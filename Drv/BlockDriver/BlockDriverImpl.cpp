#include <Drv/BlockDriver/BlockDriverImpl.hpp>
#include <Fw/FPrimeBasicTypes.hpp>
#include <Fw/Types/Assert.hpp>

namespace Drv {

    BlockDriverImpl::BlockDriverImpl(const char* compName) :
        BlockDriverComponentBase(compName), m_cycles(0)
    {

    }

    BlockDriverImpl::~BlockDriverImpl() {

    }

    void BlockDriverImpl::InterruptReport_internalInterfaceHandler(U32 ip) {
        // get time
        Os::RawTime time;
        time.now();
        // call output timing signal
        this->CycleOut_out(0,time);
        // increment cycles and write channel
        this->tlmWrite_BD_Cycles(this->m_cycles);
        this->m_cycles++;
    }

    void BlockDriverImpl::BufferIn_handler(FwIndexType portNum, Drv::DataBuffer& buffer) {
        // just a pass-through
        this->BufferOut_out(0,buffer);
    }

    void BlockDriverImpl::Sched_handler(FwIndexType portNum, U32 context) {
    }

    void BlockDriverImpl::callIsr() {
        s_driverISR(this);
    }

    void BlockDriverImpl::s_driverISR(void* arg) {
        FW_ASSERT(arg);
        // cast argument to component instance
        BlockDriverImpl* compPtr = static_cast<BlockDriverImpl*>(arg);
        compPtr->InterruptReport_internalInterfaceInvoke(0);
    }

    void BlockDriverImpl::PingIn_handler(
            const FwIndexType portNum,
            U32 key
        )
      {
        // call ping output port
        this->PingOut_out(0,key);
      }


}
