// ====================================================================== 
// \title  AssertFatalAdapterImpl.cpp
// \author tcanham
// \brief  cpp file for AssertFatalAdapter component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// 
// This software may be subject to U.S. export control laws and
// regulations.  By accepting this document, the user agrees to comply
// with all U.S. export laws and regulations.  User has the
// responsibility to obtain export licenses, or other export authority
// as may be required before exporting such information to foreign
// countries or providing access to foreign persons.
// ====================================================================== 


#include <Svc/AssertFatalAdapter/AssertFatalAdapterComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Types/Assert.hpp>
#include <assert.h>
#include <stdio.h>

namespace Svc {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  AssertFatalAdapterComponentImpl ::
#if FW_OBJECT_NAMES == 1
    AssertFatalAdapterComponentImpl(
        const char *const compName
    ) :
      AssertFatalAdapterComponentBase(compName)
#else
    AssertFatalAdapterImpl(void)
#endif
  {
      // register component with adapter
      this->m_adapter.regAssertReporter(this);
      // register adapter
      this->m_adapter.registerHook();

  }

  void AssertFatalAdapterComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    AssertFatalAdapterComponentBase::init(instance);
  }

  AssertFatalAdapterComponentImpl ::
    ~AssertFatalAdapterComponentImpl(void)
  {

  }

  void AssertFatalAdapterComponentImpl::AssertFatalAdapter::reportAssert(
          FILE_NAME_ARG file,
          NATIVE_UINT_TYPE lineNo,
          NATIVE_UINT_TYPE numArgs,
          AssertArg arg1,
          AssertArg arg2,
          AssertArg arg3,
          AssertArg arg4,
          AssertArg arg5,
          AssertArg arg6
          ) {

      if (m_compPtr) {
          m_compPtr->reportAssert(file,lineNo,numArgs,
                  arg1,arg2,arg3,arg4,arg5,arg6);
      } else {
          // Can't assert, what else can we do? Maybe somebody will see it.
          (void)printf("Svc::AssertFatalAdapter not registered!\n");
          assert(0);
      }
  }

  void AssertFatalAdapterComponentImpl::AssertFatalAdapter::regAssertReporter(AssertFatalAdapterComponentImpl* compPtr) {
      this->m_compPtr = compPtr;
  }

  AssertFatalAdapterComponentImpl::AssertFatalAdapter::AssertFatalAdapter() : m_compPtr(0) {
  }

  AssertFatalAdapterComponentImpl::AssertFatalAdapter::~AssertFatalAdapter() {
  }

  void AssertFatalAdapterComponentImpl::AssertFatalAdapter::doAssert(void) {
      // do nothing since there will be a FATAL
  }

  void AssertFatalAdapterComponentImpl::reportAssert(
          FILE_NAME_ARG file,
          NATIVE_UINT_TYPE lineNo,
          NATIVE_UINT_TYPE numArgs,
          AssertArg arg1,
          AssertArg arg2,
          AssertArg arg3,
          AssertArg arg4,
          AssertArg arg5,
          AssertArg arg6
          ) {


#if FW_ASSERT_LEVEL == FW_FILEID_ASSERT
      Fw::LogStringArg fileArg;
      fileArg.format("%d",file);
#else
      Fw::LogStringArg fileArg((const char*)file);
#endif

      switch (numArgs) {
          case 0:
              this->log_FATAL_AF_ASSERT_0(fileArg,lineNo);
              break;
          case 1:
              this->log_FATAL_AF_ASSERT_1(fileArg,lineNo,arg1);
              break;
          case 2:
              this->log_FATAL_AF_ASSERT_2(fileArg,lineNo,arg1,arg2);
              break;
          case 3:
              this->log_FATAL_AF_ASSERT_3(fileArg,lineNo,arg1,arg2,arg3);
              break;
          case 4:
              this->log_FATAL_AF_ASSERT_4(fileArg,lineNo,arg1,arg2,arg3,arg4);
              break;
          case 5:
              this->log_FATAL_AF_ASSERT_5(fileArg,lineNo,arg1,arg2,arg3,arg4,arg5);
              break;
          case 6:
              this->log_FATAL_AF_ASSERT_6(fileArg,lineNo,arg1,arg2,arg3,arg4,arg5,arg6);
              break;
          default:
              this->log_FATAL_AF_UNEXPECTED_ASSERT(fileArg,lineNo,numArgs);
              break;
      }

  }
} // end namespace Svc
