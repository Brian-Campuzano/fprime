// ======================================================================
// \title  ExternalParamTests.cpp
// \author B. Campuzano
// \brief  cpp file for external parameter tests
//
// \copyright
// Copyright (C) 2009-2025 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include "Tester.hpp"

// ----------------------------------------------------------------------
// External Parameter tests
// ----------------------------------------------------------------------

void Tester ::testExternalParam() {
    ASSERT_TRUE(component.isConnected_prmGetOut_OutputPort(0));
    component.loadParameters();

    Fw::ParamValid valid;

    bool extBoolVal = component.paramGet_ParamBoolExt(valid);
    ASSERT_EQ(valid, prmValid);
    if (valid == Fw::ParamValid::VALID) {
        ASSERT_EQ(extBoolVal, this->paramTesterDelegate.m_param_ParamBoolExt);
    }

    I32 i32Val = component.paramGet_ParamI32Ext(valid);
    ASSERT_EQ(valid, prmValid);
    if (valid == Fw::ParamValid::VALID) {
        ASSERT_EQ(i32Val, this->paramTesterDelegate.m_param_ParamI32Ext);
    }

    Fw::ParamString stringVal = component.paramGet_ParamStringExt(valid);
    if (valid == Fw::ParamValid::VALID) {
        ASSERT_EQ(stringVal, this->paramTesterDelegate.m_param_ParamStringExt);
    } else {
        ASSERT_EQ(valid, Fw::ParamValid::DEFAULT);
    }

    FormalParamEnum enumVal = component.paramGet_ParamEnumExt(valid);
    ASSERT_EQ(valid, prmValid);
    if (valid == Fw::ParamValid::VALID) {
        ASSERT_EQ(enumVal, this->paramTesterDelegate.m_param_ParamEnumExt);
    }

    FormalParamArray arrayVal = component.paramGet_ParamArrayExt(valid);
    if (valid == Fw::ParamValid::VALID) {
        ASSERT_EQ(arrayVal, this->paramTesterDelegate.m_param_ParamArrayExt);
    } else {
        ASSERT_EQ(valid, Fw::ParamValid::DEFAULT);
    }

    FormalParamStruct structVal = component.paramGet_ParamStructExt(valid);
    ASSERT_EQ(valid, prmValid);
    if (valid == Fw::ParamValid::VALID) {
        ASSERT_EQ(structVal, this->paramTesterDelegate.m_param_ParamStructExt);
    }
}

void Tester ::testExternalParamCommand(FwIndexType portNum, FppTest::Types::BoolParam& data) {
    Fw::CmdArgBuffer buf;

    // Test unsuccessful saving of param
    this->sendRawCmd(component.OPCODE_PARAMBOOLEXT_SAVE, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, component.OPCODE_PARAMBOOLEXT_SAVE, 1, Fw::CmdResponse::EXECUTION_ERROR);

    this->connectPrmSetIn();
    ASSERT_TRUE(component.isConnected_prmSetOut_OutputPort(portNum));

    // Test incorrect deserialization when setting param
    this->sendRawCmd(component.OPCODE_PARAMBOOLEXT_SET, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(2);
    ASSERT_CMD_RESPONSE(1, component.OPCODE_PARAMBOOLEXT_SET, 1, Fw::CmdResponse::VALIDATION_ERROR);

    // Test successful setting of param
    this->paramSet_ParamBoolExt(data.args.val, Fw::ParamValid::VALID);
    this->paramSend_ParamBoolExt(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(3);
    ASSERT_CMD_RESPONSE(2, component.OPCODE_PARAMBOOLEXT_SET, 1, Fw::CmdResponse::OK);

    // Test successful saving of param
    this->paramSave_ParamBoolExt(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(4);
    ASSERT_CMD_RESPONSE(3, component.OPCODE_PARAMBOOLEXT_SAVE, 1, Fw::CmdResponse::OK);
    ASSERT_EQ(this->paramTesterDelegate.m_param_ParamBoolExt, data.args.val);
}

void Tester ::testExternalParamCommand(FwIndexType portNum, FppTest::Types::I32Param& data) {
    Fw::CmdArgBuffer buf;

    // Test unsuccessful saving of param
    this->sendRawCmd(component.OPCODE_PARAMI32EXT_SAVE, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, component.OPCODE_PARAMI32EXT_SAVE, 1, Fw::CmdResponse::EXECUTION_ERROR);

    this->connectPrmSetIn();
    ASSERT_TRUE(component.isConnected_prmSetOut_OutputPort(portNum));

    // Test incorrect deserialization when setting param
    this->sendRawCmd(component.OPCODE_PARAMI32EXT_SET, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(2);
    ASSERT_CMD_RESPONSE(1, component.OPCODE_PARAMI32EXT_SET, 1, Fw::CmdResponse::VALIDATION_ERROR);

    // Test successful setting of param
    this->paramSet_ParamI32Ext(data.args.val, Fw::ParamValid::VALID);
    this->paramSend_ParamI32Ext(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(3);
    ASSERT_CMD_RESPONSE(2, component.OPCODE_PARAMI32EXT_SET, 1, Fw::CmdResponse::OK);

    // Test successful saving of param
    this->paramSave_ParamI32Ext(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(4);
    ASSERT_CMD_RESPONSE(3, component.OPCODE_PARAMI32EXT_SAVE, 1, Fw::CmdResponse::OK);
    ASSERT_EQ(this->paramTesterDelegate.m_param_ParamI32Ext, data.args.val);
}

void Tester ::testExternalParamCommand(FwIndexType portNum, FppTest::Types::PrmStringParam& data) {
    Fw::CmdArgBuffer buf;

    // Test unsuccessful saving of param
    this->sendRawCmd(component.OPCODE_PARAMSTRINGEXT_SAVE, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, component.OPCODE_PARAMSTRINGEXT_SAVE, 1, Fw::CmdResponse::EXECUTION_ERROR);

    this->connectPrmSetIn();
    ASSERT_TRUE(component.isConnected_prmSetOut_OutputPort(portNum));

    // Test incorrect deserialization when setting param
    this->sendRawCmd(component.OPCODE_PARAMSTRINGEXT_SET, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(2);
    ASSERT_CMD_RESPONSE(1, component.OPCODE_PARAMSTRINGEXT_SET, 1, Fw::CmdResponse::VALIDATION_ERROR);

    // Test successful setting of param
    this->paramSet_ParamStringExt(data.args.val, Fw::ParamValid::VALID);
    this->paramSend_ParamStringExt(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(3);
    ASSERT_CMD_RESPONSE(2, component.OPCODE_PARAMSTRINGEXT_SET, 1, Fw::CmdResponse::OK);

    // Test successful saving of param
    this->paramSave_ParamStringExt(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(4);
    ASSERT_CMD_RESPONSE(3, component.OPCODE_PARAMSTRINGEXT_SAVE, 1, Fw::CmdResponse::OK);
    ASSERT_EQ(this->paramTesterDelegate.m_param_ParamStringExt, data.args.val);
}

void Tester ::testExternalParamCommand(FwIndexType portNum, FppTest::Types::EnumParam& data) {
    Fw::CmdArgBuffer buf;

    // Test unsuccessful saving of param
    this->sendRawCmd(component.OPCODE_PARAMENUMEXT_SAVE, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, component.OPCODE_PARAMENUMEXT_SAVE, 1, Fw::CmdResponse::EXECUTION_ERROR);

    this->connectPrmSetIn();
    ASSERT_TRUE(component.isConnected_prmSetOut_OutputPort(portNum));

    // Test incorrect deserialization when setting param
    this->sendRawCmd(component.OPCODE_PARAMENUMEXT_SET, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(2);
    ASSERT_CMD_RESPONSE(1, component.OPCODE_PARAMENUMEXT_SET, 1, Fw::CmdResponse::VALIDATION_ERROR);

    // Test successful setting of param
    this->paramSet_ParamEnumExt(data.args.val, Fw::ParamValid::VALID);
    this->paramSend_ParamEnumExt(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(3);
    ASSERT_CMD_RESPONSE(2, component.OPCODE_PARAMENUMEXT_SET, 1, Fw::CmdResponse::OK);

    // Test successful saving of param
    this->paramSave_ParamEnumExt(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(4);
    ASSERT_CMD_RESPONSE(3, component.OPCODE_PARAMENUMEXT_SAVE, 1, Fw::CmdResponse::OK);
    ASSERT_EQ(this->paramTesterDelegate.m_param_ParamEnumExt, data.args.val);
}

void Tester ::testExternalParamCommand(FwIndexType portNum, FppTest::Types::ArrayParam& data) {
    Fw::CmdArgBuffer buf;

    // Test unsuccessful saving of param
    this->sendRawCmd(component.OPCODE_PARAMARRAYEXT_SAVE, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, component.OPCODE_PARAMARRAYEXT_SAVE, 1, Fw::CmdResponse::EXECUTION_ERROR);

    this->connectPrmSetIn();
    ASSERT_TRUE(component.isConnected_prmSetOut_OutputPort(portNum));

    // Test incorrect deserialization when setting param
    this->sendRawCmd(component.OPCODE_PARAMARRAYEXT_SET, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(2);
    ASSERT_CMD_RESPONSE(1, component.OPCODE_PARAMARRAYEXT_SET, 1, Fw::CmdResponse::VALIDATION_ERROR);

    // Test successful setting of param
    this->paramSet_ParamArrayExt(data.args.val, Fw::ParamValid::VALID);
    this->paramSend_ParamArrayExt(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(3);
    ASSERT_CMD_RESPONSE(2, component.OPCODE_PARAMARRAYEXT_SET, 1, Fw::CmdResponse::OK);

    // Test successful saving of param
    this->paramSave_ParamArrayExt(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(4);
    ASSERT_CMD_RESPONSE(3, component.OPCODE_PARAMARRAYEXT_SAVE, 1, Fw::CmdResponse::OK);
    ASSERT_EQ(this->paramTesterDelegate.m_param_ParamArrayExt, data.args.val);
}

void Tester ::testExternalParamCommand(FwIndexType portNum, FppTest::Types::StructParam& data) {
    Fw::CmdArgBuffer buf;

    // Test unsuccessful saving of param
    this->sendRawCmd(component.OPCODE_PARAMSTRUCTEXT_SAVE, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, component.OPCODE_PARAMSTRUCTEXT_SAVE, 1, Fw::CmdResponse::EXECUTION_ERROR);

    this->connectPrmSetIn();
    ASSERT_TRUE(component.isConnected_prmSetOut_OutputPort(portNum));

    // Test incorrect deserialization when setting param
    this->sendRawCmd(component.OPCODE_PARAMSTRUCTEXT_SET, 1, buf);

    ASSERT_CMD_RESPONSE_SIZE(2);
    ASSERT_CMD_RESPONSE(1, component.OPCODE_PARAMSTRUCTEXT_SET, 1, Fw::CmdResponse::VALIDATION_ERROR);

    // Test successful setting of param
    this->paramSet_ParamStructExt(data.args.val, Fw::ParamValid::VALID);
    this->paramSend_ParamStructExt(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(3);
    ASSERT_CMD_RESPONSE(2, component.OPCODE_PARAMSTRUCTEXT_SET, 1, Fw::CmdResponse::OK);

    // Test successful saving of param
    this->paramSave_ParamStructExt(0, 1);

    ASSERT_CMD_RESPONSE_SIZE(4);
    ASSERT_CMD_RESPONSE(3, component.OPCODE_PARAMSTRUCTEXT_SAVE, 1, Fw::CmdResponse::OK);
    ASSERT_EQ(this->paramTesterDelegate.m_param_ParamStructExt, data.args.val);
}
