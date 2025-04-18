// ======================================================================
// \title  LinuxI2cDriver/test/ut/Tester.hpp
// \author tcanham
// \brief  hpp file for LinuxI2cDriver test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "Drv/LinuxI2cDriver/LinuxI2cDriver.hpp"
#include "LinuxI2cDriverGTestBase.hpp"

namespace Drv {

  class LinuxI2cDriverTester :
    public LinuxI2cDriverGTestBase
  {

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object LinuxI2cDriverTester
      //!
      LinuxI2cDriverTester();

      //! Destroy object LinuxI2cDriverTester
      //!
      ~LinuxI2cDriverTester();

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

      //! To do
      //!
      void sendData(U32 addr, U8* data, Fw::Buffer::SizeType size);

      void open(const char* device);

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      //! Connect ports
      //!
      void connectPorts();

      //! Initialize components
      //!
      void initComponents();

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      LinuxI2cDriver component;

  };

} // end namespace Drv

#endif
