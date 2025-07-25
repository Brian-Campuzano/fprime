/*
 * CommandDispatcherTester.hpp
 *
 *  Created on: Mar 18, 2015
 *      Author: tcanham
 */

#ifndef CMDDISP_TEST_UT_TLMCHANIMPLTESTER_HPP_
#define CMDDISP_TEST_UT_TLMCHANIMPLTESTER_HPP_

#include <CommandDispatcherGTestBase.hpp>
#include <Svc/CmdDispatcher/CommandDispatcherImpl.hpp>

namespace Svc {

    class CommandDispatcherTester: public CommandDispatcherGTestBase {
        public:
            CommandDispatcherTester(Svc::CommandDispatcherImpl& inst);
            virtual ~CommandDispatcherTester();

            void runNominalDispatch();
            void runInvalidOpcodeDispatch();
            void runCommandReregister();
            void runFailedCommand();
            void runInvalidCommand();
            void runOverflowCommands();
            void runNopCommands();
            void runClearCommandTracking();

        private:
            Svc::CommandDispatcherImpl& m_impl;

            void from_compCmdSend_handler(FwIndexType portNum, FwOpcodeType opCode, U32 cmdSeq, Fw::CmdArgBuffer &args);

            void from_pingOut_handler(
                      const FwIndexType portNum, /*!< The port number*/
                      U32 key /*!< Value to return to pinger*/
                  );            // store port call
            bool m_cmdSendRcvd;
            FwOpcodeType m_cmdSendOpCode;
            U32 m_cmdSendCmdSeq;
            Fw::CmdArgBuffer m_cmdSendArgs;

            void from_seqCmdStatus_handler(FwIndexType portNum, FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdResponse &response);

            bool m_seqStatusRcvd;
            FwOpcodeType m_seqStatusOpCode;
            U32 m_seqStatusCmdSeq;
            Fw::CmdResponse m_seqStatusCmdResponse;

    };

} /* namespace Svc */

#endif /* CMDDISP_TEST_UT_TLMCHANIMPLTESTER_HPP_ */
