/*
 * TestCommand1Impl.hpp
 *
 *  Created on: Mar 28, 2014
 *      Author: tcanham
 */

#ifndef TESTCOMMANDSOURCEIMPL_HPP_
#define TESTCOMMANDSOURCEIMPL_HPP_

#include <Autocoders/Python/test/command_tester/CommandTestComponentAc.hpp>
#include <Autocoders/Python/test/stress/TestComponentAc.hpp>

class TestCommandSourceImpl: public Cmd::CommandTesterComponentBase {
    public:
        TestCommandSourceImpl(const char* compName);
        virtual ~TestCommandSourceImpl();
        void init();
        void test_TEST_CMD_1(I32 arg1, I32 arg2);
    protected:
        void cmdStatusPort_handler(FwIndexType portNum, FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdResponse& response);
        void cmdRegPort_handler(FwIndexType portNum, FwOpcodeType opCode);
    private:
        void printStatus(const Fw::CmdResponse& response);
};

#endif /* TESTCOMMANDSOURCEIMPL_HPP_ */
