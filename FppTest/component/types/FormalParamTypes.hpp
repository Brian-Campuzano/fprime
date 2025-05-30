// ======================================================================
// \title  FormalParamTypes.hpp
// \author T. Chieu
// \brief  hpp file for formal param types
//
// \copyright
// Copyright (C) 2009-2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FPP_TEST_FORMAL_PARAM_TYPES_HPP
#define FPP_TEST_FORMAL_PARAM_TYPES_HPP

#include "Fw/Cmd/CmdString.hpp"
#include "Fw/Log/LogString.hpp"
#include "Fw/Prm/PrmString.hpp"
#include "Fw/Tlm/TlmString.hpp"
#include "Fw/Types/InternalInterfaceString.hpp"
#include "Fw/Types/SerialBuffer.hpp"
#include "Fw/Types/StringTemplate.hpp"

#include "FppTest/component/active/FormalParamArrayArrayAc.hpp"
#include "FppTest/component/active/FormalParamEnumEnumAc.hpp"
#include "FppTest/component/active/FormalParamStructSerializableAc.hpp"
#include "FppTest/component/active/StringArgsPortAc.hpp"
#include "FppTest/component/active/FormalAliasArrayAliasAc.hpp"
#include "FppTest/component/active/FormalAliasEnumAliasAc.hpp"
#include "FppTest/component/active/FormalAliasStringAliasAc.hpp"
#include "FppTest/component/active/FormalAliasStringArrayArrayAc.hpp"
#include "FppTest/utils/Utils.hpp"

#define SERIAL_ARGS_BUFFER_CAPACITY 256

namespace FppTest {

namespace Types {

template <typename ArgType, typename ReturnType>
struct FormalParamsWithReturn {
    ArgType args;
};

// Empty type
struct Empty {};

template <typename ArgType>
using FormalParams = FormalParamsWithReturn<ArgType, Empty>;

// ----------------------------------------------------------------------
// Primitive types
// ----------------------------------------------------------------------

struct BoolType {
    BoolType();

    bool val;
};

struct U32Type {
    U32Type();

    U32 val;
};

struct I32Type {
    I32Type();

    I32 val;
};

struct F32Type {
    F32Type();

    F32 val;
};

struct PrimitiveTypes {
    PrimitiveTypes();

    U32 val1;
    U32 val2;
    F32 val3;
    F32 val4;
    bool val5;
    bool val6;
};

// ----------------------------------------------------------------------
// FPP types
// ----------------------------------------------------------------------

struct EnumType {
    EnumType();

    FormalParamEnum val;
};

struct EnumTypes {
    EnumTypes();

    FormalParamEnum val1;
    FormalParamEnum val2;
    FormalAliasEnum val3;
    FormalAliasEnum val4;
};

struct ArrayType {
    ArrayType();

    FormalParamArray val;
};

struct ArrayTypes {
    ArrayTypes();

    FormalParamArray val1;
    FormalParamArray val2;
    FormalAliasArray val3;
    FormalAliasArray val4;
    FormalAliasStringArray val5;
    FormalAliasStringArray val6;
};

struct StructType {
    StructType();

    FormalParamStruct val;
};

struct StructTypes {
    StructTypes();

    FormalParamStruct val1;
    FormalParamStruct val2;
};

// ----------------------------------------------------------------------
// String types
// ----------------------------------------------------------------------

using String1 = Fw::StringTemplate<80>;
using String2 = Fw::StringTemplate<100>;

struct PortStringType {
    PortStringType();

    String1 val;
};

struct PortStringTypes {
    PortStringTypes();

    String1 val1;
    String1 val2;
    String2 val3;
    String2 val4;
};

struct InternalInterfaceStringType {
    InternalInterfaceStringType();

    Fw::InternalInterfaceString val;
};

struct InternalInterfaceStringTypes {
    InternalInterfaceStringTypes();

    Fw::InternalInterfaceString val1;
    Fw::InternalInterfaceString val2;
};

struct CmdStringType {
    CmdStringType();

    Fw::CmdStringArg val;
};

struct CmdStringTypes {
    CmdStringTypes();

    Fw::CmdStringArg val1;
    Fw::CmdStringArg val2;
};

struct LogStringType {
    LogStringType();

    Fw::LogStringArg val;
};

struct LogStringTypes {
    LogStringTypes();

    Fw::LogStringArg val1;
    Fw::LogStringArg val2;
};

struct TlmStringType {
    TlmStringType();

    Fw::TlmString val;
};

struct TlmStringTypes {
    TlmStringTypes();

    Fw::TlmString val1;
    Fw::TlmString val2;
};

struct PrmStringType {
    PrmStringType();

    Fw::ParamString val;
};

struct PrmStringTypes {
    PrmStringTypes();

    Fw::ParamString val1;
    Fw::ParamString val2;
};

struct StringType {
    StringType();

    String1 val;
};

struct AliasStringArrayType {
    AliasStringArrayType();

    FormalAliasStringArray val;
};

struct StringTypes {
    StringTypes();

    String1 val1;
    String1 val2;
};

// ----------------------------------------------------------------------
// Serial type
// ----------------------------------------------------------------------

struct SerialType {
    SerialType();

    U8 data[SERIAL_ARGS_BUFFER_CAPACITY];
    Fw::SerialBuffer val;
};

// ----------------------------------------------------------------------
// Helper functions
// ----------------------------------------------------------------------

void setRandomString(Fw::StringBase& str);
void setRandomString(Fw::StringBase& str, U32 size);
FormalParamEnum getRandomFormalParamEnum();
void getRandomFormalParamArray(FormalParamArray& a);
FormalParamStruct getRandomFormalParamStruct();
void getRandomFormalStringArray(FormalAliasStringArray& a);

// ----------------------------------------------------------------------
// Typedefs
// ----------------------------------------------------------------------

typedef FormalParams<Empty> NoParams;
typedef FormalParams<BoolType> BoolParam;
typedef FormalParams<U32Type> U32Param;
typedef FormalParams<I32Type> I32Param;
typedef FormalParams<F32Type> F32Param;
typedef FormalParams<PrimitiveTypes> PrimitiveParams;
typedef FormalParams<EnumType> EnumParam;
typedef FormalParams<EnumTypes> EnumParams;
typedef FormalParams<ArrayType> ArrayParam;
typedef FormalParams<ArrayTypes> ArrayParams;
typedef FormalParams<StructType> StructParam;
typedef FormalParams<StructTypes> StructParams;
typedef FormalParams<PortStringType> PortStringParam;
typedef FormalParams<PortStringTypes> PortStringParams;
typedef FormalParams<InternalInterfaceStringType> InternalInterfaceStringParam;
typedef FormalParams<InternalInterfaceStringTypes> InternalInterfaceStringParams;
typedef FormalParams<CmdStringType> CmdStringParam;
typedef FormalParams<CmdStringTypes> CmdStringParams;
typedef FormalParams<LogStringType> LogStringParam;
typedef FormalParams<LogStringTypes> LogStringParams;
typedef FormalParams<TlmStringType> TlmStringParam;
typedef FormalParams<TlmStringTypes> TlmStringParams;
typedef FormalParams<PrmStringType> PrmStringParam;
typedef FormalParams<PrmStringTypes> PrmStringParams;
typedef FormalParams<SerialType> SerialParam;

typedef FormalParamsWithReturn<Empty, BoolType> NoParamReturn;
typedef FormalParamsWithReturn<PrimitiveTypes, U32Type> PrimitiveReturn;
typedef FormalParamsWithReturn<EnumTypes, EnumType> EnumReturn;
typedef FormalParamsWithReturn<StringTypes, StringType> StringReturn;
typedef FormalParamsWithReturn<StringTypes, FormalAliasString> StringAliasReturn;
typedef FormalParamsWithReturn<ArrayTypes, ArrayType> ArrayReturn;
typedef FormalParamsWithReturn<ArrayTypes, FormalAliasStringArray> ArrayStringAliasReturn;
typedef FormalParamsWithReturn<StructTypes, StructType> StructReturn;

}  // namespace Types

}  // namespace FppTest

#endif
