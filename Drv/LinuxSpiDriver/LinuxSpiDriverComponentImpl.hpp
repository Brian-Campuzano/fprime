// ======================================================================
// \title  LinuxSpiDriverImpl.hpp
// \author tcanham
// \brief  hpp file for LinuxSpiDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef LinuxSpiDriver_HPP
#define LinuxSpiDriver_HPP

#include "Drv/LinuxSpiDriver/LinuxSpiDriverComponentAc.hpp"

namespace Drv {

    /**
     * This was taken from the dspal_tester example
     *
     * Supported SPI frequency to talk to MPU9x50 slave device
     * MPU9x50 SPI interface supports upto 20MHz frequency. However 20MHz is not
     * reliable in our test and corrupted data is observed.
     */
    enum SpiFrequency
    {
       SPI_FREQUENCY_1MHZ = 1000000UL,
       SPI_FREQUENCY_5MHZ = 5000000UL,
       SPI_FREQUENCY_10MHZ = 10000000UL,
       SPI_FREQUENCY_15MHZ = 15000000UL,
       SPI_FREQUENCY_20MHZ = 20000000UL,
    };

    /**
     * SPI Mode Select
     *
     * Defines the SPI Clock Polarity and Phase for each SPI Transaction.
     *
     * SPI Clock Polarity(CPOL): Defines clock polarity as idle low (CPOL = 0) or idle high(CPOL = 1)
     * SPI Clock Phase(CPHA): Defines if data is shifted out on the rising clock edge and sampled
     *                        on the falling clock edge(CPHA = 0) or if data is shifted out on the
     *                        falling clock edge and sampled on the rising clock edge(CPHA=1)
     *
     */
    enum SpiMode
    {
        SPI_MODE_CPOL_LOW_CPHA_LOW, ///< (CPOL = 0, CPHA = 0)
        SPI_MODE_CPOL_LOW_CPHA_HIGH,///< (CPOL = 0, CPHA = 1)
        SPI_MODE_CPOL_HIGH_CPHA_LOW,///< (CPOL = 1, CPHA = 0)
        SPI_MODE_CPOL_HIGH_CPHA_HIGH,///< (CPOL = 1, CPHA = 1)
    };

    class LinuxSpiDriverComponentImpl final : public LinuxSpiDriverComponentBase {

        public:

            // ----------------------------------------------------------------------
            // Construction, initialization, and destruction
            // ----------------------------------------------------------------------

            //! Construct object LinuxSpiDriver
            //!
            LinuxSpiDriverComponentImpl(
                    const char * const compName /*!< The component name*/
            );

            //! Destroy object LinuxSpiDriver
            //!
            ~LinuxSpiDriverComponentImpl();

            //! Open device
            bool open(FwIndexType device,
                      FwIndexType select,
                      SpiFrequency clock,
                      SpiMode spiMode = SpiMode::SPI_MODE_CPOL_LOW_CPHA_LOW);

        private:

            // ----------------------------------------------------------------------
            // Handler implementations for user-defined typed input ports
            // ----------------------------------------------------------------------

            //! Handler implementation for SpiReadWrite
            //!
            void SpiReadWrite_handler(const FwIndexType portNum, /*!< The port number*/
            Fw::Buffer &WriteBuffer, Fw::Buffer &readBuffer);

            int m_fd;
            FwIndexType m_device;
            FwIndexType m_select;
            FwSizeType m_bytes;

    };

} // end namespace Drv

#endif
