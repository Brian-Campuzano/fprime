// ======================================================================
// \title  UdpComponentImpl.cpp
// \author mstarch
// \brief  cpp file for UdpComponentImpl component implementation class
//
// \copyright
// Copyright 2009-2020, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <limits>
#include <Drv/Udp/UdpComponentImpl.hpp>
#include <IpCfg.hpp>
#include <Fw/FPrimeBasicTypes.hpp>
#include "Fw/Types/Assert.hpp"


namespace Drv {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

UdpComponentImpl::UdpComponentImpl(const char* const compName)
    : UdpComponentBase(compName) {}

SocketIpStatus UdpComponentImpl::configureSend(const char* hostname,
                                                 const U16 port,
                                                 const U32 send_timeout_seconds,
                                                 const U32 send_timeout_microseconds) {
    return m_socket.configureSend(hostname, port, send_timeout_seconds, send_timeout_microseconds);
}

SocketIpStatus UdpComponentImpl::configureRecv(const char* hostname, const U16 port, FwSizeType buffer_size) {
    FW_ASSERT(buffer_size <= std::numeric_limits<U32>::max(), static_cast<FwAssertArgType>(buffer_size));
    m_allocation_size = buffer_size; // Store the buffer size

    return m_socket.configureRecv(hostname, port);
}

UdpComponentImpl::~UdpComponentImpl() {}

U16 UdpComponentImpl::getRecvPort() {
    return this->m_socket.getRecvPort();
}

// ----------------------------------------------------------------------
// Implementations for socket read task virtual methods
// ----------------------------------------------------------------------

IpSocket& UdpComponentImpl::getSocketHandler() {
    return m_socket;
}

Fw::Buffer UdpComponentImpl::getBuffer() {
    return allocate_out(0, static_cast<U32>(m_allocation_size));
}

void UdpComponentImpl::sendBuffer(Fw::Buffer buffer, SocketIpStatus status) {
    Drv::RecvStatus recvStatus = RecvStatus::RECV_ERROR;
    if (status == SOCK_SUCCESS) {
        recvStatus = RecvStatus::RECV_OK;
    }
    else if (status == SOCK_NO_DATA_AVAILABLE) {
        recvStatus = RecvStatus::RECV_NO_DATA;
    }
    else {
        recvStatus = RecvStatus::RECV_ERROR;
    }
    this->recv_out(0, buffer, recvStatus);
}

void UdpComponentImpl::connected() {
    if (isConnected_ready_OutputPort(0)) {
        this->ready_out(0);
    }
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

Drv::SendStatus UdpComponentImpl::send_handler(const FwIndexType portNum, Fw::Buffer& fwBuffer) {
    Drv::SocketIpStatus status = send(fwBuffer.getData(), fwBuffer.getSize());
    // Always return the buffer
    deallocate_out(0, fwBuffer);
    if ((status == SOCK_DISCONNECTED) || (status == SOCK_INTERRUPTED_TRY_AGAIN)) {
        return SendStatus::SEND_RETRY;
    } else if (status != SOCK_SUCCESS) {
        return SendStatus::SEND_ERROR;
    }
    return SendStatus::SEND_OK;
}

}  // end namespace Drv
