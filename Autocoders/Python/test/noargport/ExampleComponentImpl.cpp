// ======================================================================
// \title  ExampleComponentImpl.cpp
// \author joshuaa
// \brief  cpp file for Example component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Autocoders/Python/test/noargport/ExampleComponentImpl.hpp>
#include <Fw/FPrimeBasicTypes.hpp>

namespace ExampleComponents {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ExampleComponentImpl ::
    ExampleComponentImpl(
        const char *const compName
    ) : ExampleComponentBase(compName)
  {

  }

  void ExampleComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    ExampleComponentBase::init(queueDepth, instance);
  }

  ExampleComponentImpl ::
    ~ExampleComponentImpl()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ExampleComponentImpl ::
    noArgPort_handler(
        const FwIndexType portNum
    )
  {
    // TODO
  }

  void ExampleComponentImpl ::
    asyncNoArgPort_handler(
        const FwIndexType portNum
    )
  {
    // TODO
  }

  void ExampleComponentImpl ::
    guardedNoArgPort_handler(
        const FwIndexType portNum
    )
  {
    // TODO
  }

  U32 ExampleComponentImpl ::
    exampleInput_handler(
        const FwIndexType portNum
    )
  {
    return 0;
  }

} // end namespace ExampleComponents
