// ======================================================================
// \title Os/Task.cpp
// \brief common function implementation for Os::Task
// ======================================================================
#include <Os/Task.hpp>
#include <Fw/Types/Assert.hpp>

namespace Os {

TaskInterface::Arguments::Arguments(const Fw::StringBase &name, const Os::TaskInterface::taskRoutine routine,
                                    void * const routine_argument, const FwTaskPriorityType priority,
                                    const FwSizeType stackSize, const FwSizeType cpuAffinity,
                                    const FwTaskIdType identifier) :
    m_name(name),
    m_routine(routine),
    m_routine_argument(routine_argument),
    m_priority(priority),
    m_stackSize(stackSize),
    m_cpuAffinity(cpuAffinity),
    m_identifier(identifier)
{
    FW_ASSERT(routine != nullptr);
}

Task::TaskRoutineWrapper::TaskRoutineWrapper(Task& self) : m_task(self) {}

void Task::TaskRoutineWrapper::run(void* wrapper_pointer) {
    FW_ASSERT(wrapper_pointer != nullptr);
    TaskRoutineWrapper& wrapper = *reinterpret_cast<TaskRoutineWrapper*>(wrapper_pointer);
    FW_ASSERT(wrapper.m_user_function != nullptr);

    wrapper.m_task.m_lock.lock();
    Task::State state = wrapper.m_task.m_state;
    wrapper.m_task.m_lock.unlock();
    FW_ASSERT(state != Task::State::NOT_STARTED);
    // Run once start code
    if (state == Task::State::STARTING) {
        wrapper.m_task.m_lock.lock();
        wrapper.m_task.m_state = Task::State::RUNNING;
        wrapper.m_task.m_lock.unlock();
        wrapper.m_task.onStart();
    }

    // Call user function supplying the user argument
    wrapper.m_user_function(wrapper.m_user_argument);
}

void Task::TaskRoutineWrapper::invoke() {
    TaskRoutineWrapper::run(this);
}

TaskRegistry* Task::s_taskRegistry = nullptr;
FwSizeType Task::s_numTasks = 0;
Mutex Task::s_taskMutex;

bool TaskInterface::isCooperative() {
    return false;
}

Task::Task() : m_wrapper(*this), m_handle_storage(), m_delegate(*TaskInterface::getDelegate(m_handle_storage)) {}

Task::~Task() {
    // If a registry has been registered and the task has been started then remove task from the registry
    if ((Task::s_taskRegistry != nullptr) && this->m_registered) {
        Task::s_taskRegistry->removeTask(this);
    }
    m_delegate.~TaskInterface();
}

void Task::suspend() {
    this->suspend(Task::SuspensionType::UNINTENTIONAL);
}

Task::State Task::getState() {
    Task::State state;
    this->m_lock.lock();
    state = this->m_state;
    this->m_lock.unlock();
    return state;
}

Task::Status Task::start(const Fw::StringBase &name, const taskRoutine routine, void* const arg,
                         const FwTaskPriorityType priority, const ParamType stackSize, const ParamType cpuAffinity,
                         const ParamType identifier) {
    FW_ASSERT(routine != nullptr);
    return this->start(Task::Arguments(name, routine, arg,
                                       priority,
                                       stackSize,
                                       cpuAffinity,
                                       static_cast<FwTaskIdType>(identifier)));
}


Task::Status Task::start(const Task::Arguments& arguments) {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<TaskInterface*>(&this->m_handle_storage[0]));
    FW_ASSERT(arguments.m_routine != nullptr);
    this->m_name = arguments.m_name;
    this->m_state = State::STARTING;

    Arguments wrapped_arguments = arguments;
    // Intercept routine and argument with the local wrapper
    this->m_wrapper.m_user_function = arguments.m_routine;
    this->m_wrapper.m_user_argument = arguments.m_routine_argument;
    wrapped_arguments.m_routine = Task::TaskRoutineWrapper::run;
    wrapped_arguments.m_routine_argument = &this->m_wrapper;

    Task::Status status = this->m_delegate.start(wrapped_arguments);
    if (status == Task::Status::OP_OK) {
        Task::m_lock.lock();
        this->m_priority = wrapped_arguments.m_priority;
        Task::m_lock.unlock();
        Task::s_taskMutex.lock();
        Task::s_numTasks++;
        Task::s_taskMutex.unlock();

        // If a registry has been registered, register task to it
        if (Task::s_taskRegistry) {
            Task::s_taskRegistry->addTask(this);
            this->m_registered = true;
        }
    }
    return status;
}

void Task::onStart() {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<TaskInterface*>(&this->m_handle_storage[0]));
    this->m_delegate.onStart();
}

void Task::invokeRoutine() {
    this->m_wrapper.invoke();
}

Task::Status Task::join() {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<TaskInterface*>(&this->m_handle_storage[0]));
    Task::Status status = Task::Status::INVALID_STATE;
    Task::State state = this->getState();
    if (state == Task::RUNNING || state == STARTING) {
        status = this->m_delegate.join();
        this->m_lock.lock();
        if (status == Task::Status::OP_OK) {
            this->m_state = Task::State::EXITED;
        } else {
            this->m_state = Task::State::UNKNOWN;
        }
        this->m_lock.unlock();
    }
    return status;
}

void Task::suspend(Task::SuspensionType suspensionType) {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<TaskInterface*>(&this->m_handle_storage[0]));
    this->m_delegate.suspend(suspensionType);
    this->m_lock.lock();
    this->m_state = (suspensionType == Task::SuspensionType::INTENTIONAL) ? State::SUSPENDED_INTENTIONALLY : State::SUSPENDED_UNINTENTIONALLY;
    this->m_lock.unlock();
}

void Task::resume() {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<TaskInterface*>(&this->m_handle_storage[0]));
    this->m_delegate.resume();
}

bool Task::isCooperative() {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<TaskInterface*>(&this->m_handle_storage[0]));
    return this->m_delegate.isCooperative();
}

FwTaskPriorityType Task::getPriority() {
    Os::ScopeLock lock(this->m_lock);
    return this->m_priority;
}

TaskHandle* Task::getHandle() {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<TaskInterface*>(&this->m_handle_storage[0]));
    return this->m_delegate.getHandle();
}

FwSizeType Task::getNumTasks() {
    Task::s_taskMutex.lock();
    FwSizeType num_tasks = Task::s_numTasks;
    Task::s_taskMutex.unlock();
    return num_tasks;
}

Os::TaskInterface::Status Task::_delay(Fw::TimeInterval interval) {
    FW_ASSERT(&this->m_delegate == reinterpret_cast<TaskInterface*>(&this->m_handle_storage[0]));
    return this->m_delegate._delay(interval);
}

Os::TaskInterface::Status Task::delay(Fw::TimeInterval interval) {
    return Task::getSingleton()._delay(interval);
}

void Task::init() {
    // Force trigger on the fly singleton setup
    (void) Task::getSingleton();
}

Task& Task::getSingleton() {
    static Task s_singleton;
    return s_singleton;
}

void Task::registerTaskRegistry(TaskRegistry* registry) {
    Task::s_taskRegistry = registry;
}
}
