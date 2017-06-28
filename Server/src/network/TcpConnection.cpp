//
// Created by FyS on 23/05/17.
//

#include <boost/bind.hpp>
#include <iostream>
#include <Gateway.hh>
#include "TcpConnection.hh"

fys::network::TcpConnection::TcpConnection(boost::asio::io_service& io_service) : _isShuttingDown(false), _socket(io_service) {
}

boost::asio::ip::tcp::socket& fys::network::TcpConnection::getSocket() {
    return _socket;
}

void fys::network::TcpConnection::send(const fys::network::Message& msg) {

}

void fys::network::TcpConnection::handleWrite(const boost::system::error_code &error, size_t bytesTransferred) {
    if (error || _isShuttingDown)
        shuttingConnectionDown();
}

void fys::network::TcpConnection::handleRead(const boost::system::error_code &error, size_t bytesTransferred, fys::mq::FysBus<fys::network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr &fysBus) {
    if (!error && !_isShuttingDown && bytesTransferred > 1) {
        Message message(_buffer);
        std::cout << "Raw Message to write on bus :" << _buffer << std::endl;
        fysBus->pushInBus(message);
        readOnSocket(fysBus);
    }
    else
        shuttingConnectionDown();
}

void fys::network::TcpConnection::readOnSocket(fys::mq::FysBus<fys::network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr &fysBus) {
    std::fill(_buffer, _buffer + fys::network::BUFFER_SIZE, 0);
_socket.async_read_some(boost::asio::buffer(_buffer, fys::network::BUFFER_SIZE),
    boost::bind(&TcpConnection::handleRead, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred,
                fysBus));
}

void fys::network::TcpConnection::shuttingConnectionDown() {
    if (!_isShuttingDown) {
        std::cout << "Shutting down connection..." << std::endl;
        _isShuttingDown = true;
        try {
            _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            _socket.close();
        }
        catch (std::exception &) {}
    }
}
