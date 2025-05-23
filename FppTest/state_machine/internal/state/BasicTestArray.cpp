// ======================================================================
//
// \title  BasicTestArray.hpp
// \author R. Bocchino
// \brief  Test class for basic state machine with TestArray actions (implementation)
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/state/BasicTestArray.hpp"
#include "STest/STest/Pick/Pick.hpp"

namespace FppTest {

namespace SmState {

BasicTestArray::BasicTestArray() : BasicTestArrayStateMachineBase(), m_action_a_history(), m_action_b_history() {}

void BasicTestArray::action_a(Signal signal) {
    this->m_action_a_history.push(signal);
}

void BasicTestArray::action_b(Signal signal, const SmHarness::TestArray& value) {
    this->m_action_b_history.push(signal, value);
}

void BasicTestArray::test() {
    this->m_action_a_history.clear();
    const FwEnumStoreType id = SmHarness::Pick::stateMachineId();
    this->initBase(id);
    ASSERT_EQ(this->m_id, id);
    ASSERT_EQ(this->getState(), State::S);
    ASSERT_EQ(this->m_action_a_history.getSize(), 0);
    const SmHarness::TestArray value = SmHarness::Pick::testArray();
    this->sendSignal_s(value);
    ASSERT_EQ(this->getState(), State::T);
    this->sendSignal_s(value);
    ASSERT_EQ(this->getState(), State::T);
    const FwIndexType expectedASize = 5;
    ASSERT_EQ(this->m_action_a_history.getSize(), expectedASize);
    for (FwIndexType i = 0; i < expectedASize; i++) {
        ASSERT_EQ(this->m_action_a_history.getItemAt(i), Signal::s);
    }
    ASSERT_EQ(this->m_action_b_history.getSize(), 1);
    ASSERT_EQ(this->m_action_b_history.getSignals().getItemAt(0), Signal::s);
    ASSERT_EQ(this->m_action_b_history.getValues().getItemAt(0), value);
}

}  // namespace SmState

}  // end namespace FppTest
