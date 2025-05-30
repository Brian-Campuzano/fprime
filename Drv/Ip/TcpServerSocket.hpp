// ======================================================================
// \title  TcpServerSocket.hpp
// \author mstarch
// \brief  hpp file for TcpServerSocket core implementation classes
//
// \copyright
// Copyright 2009-2020, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================
#ifndef DRV_TCPSERVER_TCPHELPER_HPP_
#define DRV_TCPSERVER_TCPHELPER_HPP_

#include <Fw/FPrimeBasicTypes.hpp>
#include <Drv/Ip/IpSocket.hpp>
#include <config/IpCfg.hpp>

namespace Drv {

/**
 * \brief Helper for setting up Tcp using Berkeley sockets as a server
 *
 * Certain IP headers have conflicting definitions with the m_data member of various types in fprime. TcpServerSocket
 * separates the ip setup from the incoming Fw::Buffer in the primary component class preventing this collision.
 */
class TcpServerSocket : public IpSocket {
  public:
    /**
     * \brief Constructor for client socket tcp implementation
     */
    TcpServerSocket();

    /**
     * \brief Opens the server socket and listens, does not block.
     *
     * Opens the server's listening socket such that this server can listen for incoming client requests. Given the
     * nature of this component, only one (1) client can be handled at a time. After this call succeeds, clients may
     * connect. This call does not block, block occurs on `open` while waiting to accept incoming clients.
     * \param socketDescriptor: server descriptor will be written here
     * \return status of the server socket setup.
     */
    SocketIpStatus startup(SocketDescriptor& socketDescriptor);

    /**
     * \brief close the server socket created by the `startup` call
     *
     * Calls the close function on the server socket. No shutdown is performed on the server socket, as that is left to
     * the individual client sockets.
     *
     * \param socketDescriptor:  descriptor to close
     */
    void terminate(const SocketDescriptor& socketDescriptor);

    /**
     * \brief get the port being listened on
     *
     * Most useful when listen was configured to use port "0", this will return the port used for listening after a port
     * has been determined. Will return 0 if the connection has not been setup.
     *
     * \return receive port
     */
    U16 getListenPort();

  protected:
    /**
     * \brief Tcp specific implementation for opening a client socket connected to this server.
     * \param socketDescriptor: (output) descriptor opened. Only valid on SOCK_SUCCESS. Otherwise will be invalid
     * \return status of open
     */
    SocketIpStatus openProtocol(SocketDescriptor& socketDescriptor) override;
    /**
     * \brief Protocol specific implementation of send.  Called directly with retry from send.
     * \param socketDescriptor: descriptor to send to
     * \param data: data to send
     * \param size: size of data to send
     * \return: size of data sent, or -1 on error.
     */
    I32 sendProtocol(const SocketDescriptor& socketDescriptor, const U8* const data, const U32 size) override;
    /**
     * \brief Protocol specific implementation of recv.  Called directly with error handling from recv.
     * \param socketDescriptor: descriptor to recv from
     * \param data: data pointer to fill
     * \param size: size of data buffer
     * \return: size of data received, or -1 on error.
     */
    I32 recvProtocol(const SocketDescriptor& socketDescriptor, U8* const data, const U32 size) override;



};
}  // namespace Drv

#endif /* DRV_TCPSERVER_TCPHELPER_HPP_ */
