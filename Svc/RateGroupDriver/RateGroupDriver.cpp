#include <Svc/RateGroupDriver/RateGroupDriver.hpp>
#include <Fw/FPrimeBasicTypes.hpp>
#include <cstring>
#include <Fw/Types/Assert.hpp>
#include <cstdio>

namespace Svc {

    RateGroupDriver::RateGroupDriver(const char* compName) :
        RateGroupDriverComponentBase(compName),
    m_ticks(0),m_rollover(1),m_configured(false) {

    }

    void RateGroupDriver::configure(const DividerSet& dividerSet)
    {

        // check arguments
        FW_ASSERT(dividerSet.dividers);
        // verify port/table size matches
        FW_ASSERT(FW_NUM_ARRAY_ELEMENTS(this->m_dividers) == this->getNum_CycleOut_OutputPorts(),
                static_cast<FwAssertArgType>(FW_NUM_ARRAY_ELEMENTS(this->m_dividers)),
                static_cast<FwAssertArgType>(this->getNum_CycleOut_OutputPorts()));
        // copy provided array of dividers
        for (FwIndexType entry = 0; entry < RateGroupDriver::DIVIDER_SIZE; entry++) {
            // A port with an offset equal or bigger than the divisor is not accepted because it would never be called
            FW_ASSERT((dividerSet.dividers[entry].offset==0) || (dividerSet.dividers[entry].offset < dividerSet.dividers[entry].divisor),
                static_cast<FwAssertArgType>(dividerSet.dividers[entry].offset),
                static_cast<FwAssertArgType>(dividerSet.dividers[entry].divisor));
            this->m_dividers[entry] = dividerSet.dividers[entry];
            // rollover value should be product of all dividers to make sure integer rollover doesn't jump cycles
            // only use non-zero dividers
            if (dividerSet.dividers[entry].divisor != 0) {
                // Ensure that rollover will not overflow
                FW_ASSERT((std::numeric_limits<FwSizeType>::max() / dividerSet.dividers[entry].divisor) >= this->m_rollover,
                        static_cast<FwAssertArgType>(this->m_rollover),
                        static_cast<FwAssertArgType>(dividerSet.dividers[entry].divisor));
                this->m_rollover *= dividerSet.dividers[entry].divisor;
            }
        }
        this->m_configured = true;
    }

    RateGroupDriver::~RateGroupDriver() {

    }

    void RateGroupDriver::CycleIn_handler(FwIndexType portNum, Os::RawTime& cycleStart) {

        // Make sure that the dividers have been configured:
        // If this asserts, add the configure() call to initialization.
        FW_ASSERT(this->m_configured);

        // Loop through each divider. For a given port, the port will be called when the divider value
        // divides evenly into the number of ticks. For example, if the divider value for a port is 4,
        // it would be called every fourth invocation of the CycleIn port.
        for (FwIndexType entry = 0; entry < RateGroupDriver::DIVIDER_SIZE; entry++) {
            if (this->m_dividers[entry].divisor != 0) {
                if (this->isConnected_CycleOut_OutputPort(static_cast<FwIndexType>(entry))) {
                    if ((this->m_ticks % this->m_dividers[entry].divisor) == this->m_dividers[entry].offset) {
                        this->CycleOut_out(static_cast<FwIndexType>(entry),cycleStart);
                    }
                }
            }
        }

        // rollover the tick value when the tick count reaches the rollover value
        // the rollover value is the product of all the dividers. See comment in constructor.
        this->m_ticks = (this->m_ticks + 1) % this->m_rollover;

    }

}
