// ======================================================================
// \title  ChoiceTester.cpp
// \author bocchino
// \brief  cpp file for ChoiceTester component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/initial/ChoiceTester.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceInitial {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ChoiceTester::ChoiceTester(const char* const compName)
    : ChoiceComponentBase(compName),
      m_choice_action_a_history(),
      m_smInitialChoice_action_a_history(),
      m_choice_guard_g(),
      m_smInitialChoice_guard_g() {}

ChoiceTester::~ChoiceTester() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void ChoiceTester::FppTest_SmInitial_Choice_action_a(SmId smId, FppTest_SmInitial_Choice::Signal signal) {
    ASSERT_EQ(smId, SmId::smInitialChoice);
    this->m_smInitialChoice_action_a_history.push(signal);
}

void ChoiceTester::FppTest_SmInstanceInitial_Choice_Choice_action_a(
    SmId smId,
    FppTest_SmInstanceInitial_Choice_Choice::Signal signal) {
    ASSERT_EQ(smId, SmId::choice);
    this->m_choice_action_a_history.push(signal);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool ChoiceTester ::FppTest_SmInitial_Choice_guard_g(SmId smId, FppTest_SmInitial_Choice::Signal signal) const {
    FW_ASSERT(smId == SmId::smInitialChoice, static_cast<FwAssertArgType>(smId));
    return m_smInitialChoice_guard_g.call(signal);
}

bool ChoiceTester ::FppTest_SmInstanceInitial_Choice_Choice_guard_g(
    SmId smId,
    FppTest_SmInstanceInitial_Choice_Choice::Signal signal) const {
    FW_ASSERT(smId == SmId::choice, static_cast<FwAssertArgType>(smId));
    return m_choice_guard_g.call(signal);
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void ChoiceTester::testFalse() {
    this->m_choice_action_a_history.clear();
    this->m_smInitialChoice_action_a_history.clear();
    this->m_choice_guard_g.reset();
    this->m_smInitialChoice_guard_g.reset();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->choice_getState(), Choice_Choice::State::T);
    ASSERT_EQ(this->smInitialChoice_getState(), SmInitial_Choice::State::T);
    const FwIndexType expectedActionSize = 5;
    const FwIndexType expectedGuardSize = 1;
    this->checkActionsAndGuards(expectedActionSize, expectedGuardSize);
}

void ChoiceTester::testTrue() {
    this->m_choice_action_a_history.clear();
    this->m_smInitialChoice_action_a_history.clear();
    this->m_choice_guard_g.reset();
    this->m_smInitialChoice_guard_g.reset();
    this->m_choice_guard_g.setReturnValue(true);
    this->m_smInitialChoice_guard_g.setReturnValue(true);
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->choice_getState(), Choice_Choice::State::S);
    ASSERT_EQ(this->smInitialChoice_getState(), SmInitial_Choice::State::S);
    const FwIndexType expectedActionSize = 3;
    const FwIndexType expectedGuardSize = 1;
    this->checkActionsAndGuards(expectedActionSize, expectedGuardSize);
}

// ----------------------------------------------------------------------
// Helper functions
// ----------------------------------------------------------------------

void ChoiceTester::checkActionsAndGuards(FwIndexType expectedActionSize, FwIndexType expectedGuardSize) {
    ASSERT_EQ(this->m_choice_action_a_history.getSize(), expectedActionSize);
    ASSERT_EQ(this->m_smInitialChoice_action_a_history.getSize(), expectedActionSize);
    for (FwIndexType i = 0; i < expectedActionSize; i++) {
        ASSERT_EQ(this->m_choice_action_a_history.getItemAt(i), Choice_Choice::Signal::__FPRIME_AC_INITIAL_TRANSITION);
        ASSERT_EQ(this->m_smInitialChoice_action_a_history.getItemAt(i),
                  SmInitial_Choice::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }
    ASSERT_EQ(this->m_choice_guard_g.getCallHistory().getSize(), expectedGuardSize);
    ASSERT_EQ(this->m_smInitialChoice_guard_g.getCallHistory().getSize(), expectedGuardSize);
    for (FwIndexType i = 0; i < expectedGuardSize; i++) {
        ASSERT_EQ(this->m_choice_guard_g.getCallHistory().getItemAt(i),
                  Choice_Choice::Signal::__FPRIME_AC_INITIAL_TRANSITION);
        ASSERT_EQ(this->m_smInitialChoice_guard_g.getCallHistory().getItemAt(i),
                  SmInitial_Choice::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }
}

}  // namespace SmInstanceInitial

}  // namespace FppTest
