// ======================================================================
// \title  IpSocket.hpp
// \author mstarch
// \brief  hpp file for IpSocket core implementation classes
//
// \copyright
// Copyright 2009-2020, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================
#ifndef DRV_IP_IPHELPER_HPP_
#define DRV_IP_IPHELPER_HPP_

#include <Fw/FPrimeBasicTypes.hpp>
#include <config/IpCfg.hpp>
#include <Os/Mutex.hpp>

namespace Drv {

struct SocketDescriptor final {
    int fd = -1; //!< Used for all sockets to track the communication file descriptor
    int serverFd = -1; //!< Used for server sockets to track the listening file descriptor
};

/**
 * \brief Status enumeration for socket return values
 */
enum SocketIpStatus {
    SOCK_SUCCESS = 0,                        //!< Socket operation successful
    SOCK_FAILED_TO_GET_SOCKET = -1,          //!< Socket open failed
    SOCK_FAILED_TO_GET_HOST_IP = -2,         //!< Host IP lookup failed
    SOCK_INVALID_IP_ADDRESS = -3,            //!< Bad IP address supplied
    SOCK_FAILED_TO_CONNECT = -4,             //!< Failed to connect socket
    SOCK_FAILED_TO_SET_SOCKET_OPTIONS = -5,  //!< Failed to configure socket
    SOCK_INTERRUPTED_TRY_AGAIN = -6,         //!< Interrupted status for retries
    SOCK_READ_ERROR = -7,                    //!< Failed to read socket
    SOCK_DISCONNECTED = -8,                  //!< Failed to read socket with disconnect
    SOCK_FAILED_TO_BIND = -9,                //!< Failed to bind to socket
    SOCK_FAILED_TO_LISTEN = -10,             //!< Failed to listen on socket
    SOCK_FAILED_TO_ACCEPT = -11,             //!< Failed to accept connection
    SOCK_SEND_ERROR = -13,                   //!< Failed to send after configured retries
    SOCK_NOT_STARTED = -14,                  //!< Socket has not been started
    SOCK_FAILED_TO_READ_BACK_PORT = -15,     //!< Failed to read back port from connection
    SOCK_NO_DATA_AVAILABLE = -16,            //!< No data available or read operation would block
    SOCK_ANOTHER_THREAD_OPENING = -17,       //!< Another thread is opening
    SOCK_AUTO_CONNECT_DISABLED = -18,        //!< Automatic connections are disabled
    SOCK_INVALID_CALL = -19                  //!< Operation is invalid
};

/**
 * \brief Helper base-class for setting up Berkeley sockets
 *
 * Certain IP headers have conflicting definitions with the m_data member of various types in fprime. TcpHelper
 * separates the ip setup from the incoming Fw::Buffer in the primary component class preventing this collision.
 */
class IpSocket {
  public:
    IpSocket();
    virtual ~IpSocket(){};
    /**
     * \brief configure the ip socket with host and transmission timeouts
     *
     * Configures the IP handler (Tcp, Tcp server, and Udp) to use the given hostname and port. When multiple ports are
     * used for send/receive these settings affect the send direction (as is the case for udp). Hostname DNS translation
     * is left up to the caller and thus hostname must be an IP address in dot-notation of the form "x.x.x.x". Port
     * cannot be set to 0 as dynamic port assignment is not supported.
     *
     * Note: for UDP sockets this is equivalent to `configureSend` and only sets up the transmission direction of the
     * socket.  A separate call to `configureRecv` is required to receive on the socket and should be made before the
     * `open` call has been made.
     *
     * \param hostname: socket uses for outgoing transmissions (and incoming when tcp). Must be of form x.x.x.x
     * \param port: port socket uses for outgoing transmissions (and incoming when tcp). Must NOT be 0.
     * \param send_timeout_seconds: send timeout seconds portion
     * \param send_timeout_microseconds: send timeout microseconds portion. Must be less than 1000000
     * \return status of configure
     */
    virtual SocketIpStatus configure(const char* hostname, const U16 port, const U32 send_timeout_seconds,
                                     const U32 send_timeout_microseconds);

    /**
     * \brief open the IP socket for communications
     *
     * This will open the IP socket for communication. This method error checks and validates properties set using the
     * `configure` method.  Tcp sockets will open bidirectional communication assuming the `configure` function was
     * previously called. Udp sockets allow `configureRecv` and `configure`/`configureSend` calls to configure for
     * each direction separately and may be operated in a single-direction or bidirectional mode. This call returns a
     * status of SOCK_SEND means the port is ready for transmissions and any other status should be treated as an error
     * with the socket not capable of sending nor receiving. This method will properly close resources on any
     * unsuccessful status.
     *
     * In the case of server components (TcpServer) this function will block until a client has connected.
     *
     * Note: delegates to openProtocol for protocol specific implementation
     *
     * \param socketDescriptor: socket descriptor to update with opened port
     * \return status of open
     */
    SocketIpStatus open(SocketDescriptor& socketDescriptor);
    /**
     * \brief send data out the IP socket from the given buffer
     *
     * Sends data out of the IpSocket. This outgoing transmission will be retried several times if the transmission
     * fails to send all the data. Retries are globally configured in the `IpCfg.hpp` header. Should the
     * socket be unavailable, SOCK_DISCONNECTED is returned and the socket should be reopened using the `open` call.
     * This can happen even when the socket has already been opened should a transmission error/closure be detected.
     * Unless an error is received, all data will have been transmitted.
     *
     * Note: delegates to `sendProtocol` to send the data
     *
     * \param fd: file descriptor to send to
     * \param data: pointer to data to send
     * \param size: size of data to send
     * \return status of the send, SOCK_DISCONNECTED to reopen, SOCK_SUCCESS on success, something else on error
     */
    virtual SocketIpStatus send(const SocketDescriptor& socketDescriptor, const U8* const data, const U32 size);
    /**
     * \brief receive data from the IP socket from the given buffer
     *
     * Receives data from the IpSocket. Should the socket be unavailable, SOCK_DISCONNECTED will be returned and
     * the socket should be reopened using the `open` call. This can happen even when the socket has already been opened
     * should a transmission error/closure be detected. Since this blocks until data is available, it will retry as long
     * as EINTR is set and less than a max number of iterations has passed. This function will block to receive data and
     * will retry (up to a configured set of retries) as long as EINTR is returned.
     *
     * Note: delegates to `recvProtocol` to send the data
     *
     * \param socketDescriptor: socket descriptor to recv from
     * \param data: pointer to data to fill with received data
     * \param size: maximum size of data buffer to fill
     * \return status of the send, SOCK_DISCONNECTED to reopen, SOCK_SUCCESS on success, something else on error
     */
    SocketIpStatus recv(const SocketDescriptor& fd, U8* const data, U32& size);

    /**
     * \brief closes the socket
     *
     * Closes the socket opened by the open call. In this case of the TcpServer, this does NOT close server's listening
     * port but will close the active client connection.
     *
     * \param socketDescriptor: socket descriptor to close
     */
    void close(const SocketDescriptor& socketDescriptor);

    /**
     * \brief shutdown the socket
     *
     * Shuts down the socket opened by the open call. In this case of the TcpServer, this does shut down server's
     * listening port, but rather shuts down the active client.
     *
     * A shut down begins the termination of communication. The underlying socket will coordinate a clean shutdown, and
     * it is safe to close the socket once a recv with 0 size has returned or an appropriate timeout has been reached.
     *
     * \param socketDescriptor: socket descriptor to shutdown
     */
    void shutdown(const SocketDescriptor& socketDescriptor);

  protected:
    /**
     * \brief Check if the given port is valid for the socket
     *
     * Some ports should be allowed for sockets and disabled on others (e.g. port 0 is a valid tcp server port but not a
     * client. This will check the port and return "true" if the port is valid, or "false" otherwise. In the default
     * implementation, all ports are considered valid.
     *
     * \param port: port to check
     * \return true if valid, false otherwise
     */
    virtual bool isValidPort(U16 port);

    /**
     * \brief setup the socket timeout properties of the opened outgoing socket
     * \param socketDescriptor: socket descriptor to setup
     * \return status of timeout setup
    */
    SocketIpStatus setupTimeouts(int socketFd);

    /**
     * \brief converts a given address in dot form x.x.x.x to an ip address. ONLY works for IPv4.
     * \param address: address to convert
     * \param ip4: IPv4 representation structure to fill
     * \return: status of conversion
     */
    static SocketIpStatus addressToIp4(const char* address, void* ip4);
    /**
     * \brief Protocol specific open implementation, called from open.
     * \param socketDescriptor: (output) socket descriptor opened. Only valid on SOCK_SUCCESS. Otherwise will be invalid
     * \return status of open
     */
    virtual SocketIpStatus openProtocol(SocketDescriptor& fd) = 0;
    /**
     * \brief Protocol specific implementation of send.  Called directly with retry from send.
     * \param socketDescriptor: socket descriptor to send to
     * \param data: data to send
     * \param size: size of data to send
     * \return: size of data sent, or -1 on error.
     */
    virtual I32 sendProtocol(const SocketDescriptor& socketDescriptor, const U8* const data, const U32 size) = 0;

    /**
     * \brief Protocol specific implementation of recv.  Called directly with error handling from recv.
     * \param socketDescriptor: socket descriptor to recv from
     * \param data: data pointer to fill
     * \param size: size of data buffer
     * \return: size of data received, or -1 on error.
     */
    virtual I32 recvProtocol(const SocketDescriptor& socketDescriptor, U8* const data, const U32 size) = 0;

    /**
     * \brief Handle zero return from recvProtocol
     *
     * This method is called when recvProtocol returns 0. The default implementation
     * treats this as a disconnection (appropriate for TCP). Subclasses can override
     * this to provide different behavior.
     *
     * @return SocketIpStatus Status to return from recv
     */
    virtual SocketIpStatus handleZeroReturn();

    U32 m_timeoutSeconds;
    U32 m_timeoutMicroseconds;
    U16 m_port;  //!< IP address port used
    char m_hostname[SOCKET_MAX_HOSTNAME_SIZE];  //!< Hostname to supply
};
}  // namespace Drv

#endif /* DRV_SOCKETIPDRIVER_SOCKETHELPER_HPP_ */
