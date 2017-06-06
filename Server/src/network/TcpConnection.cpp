//
// Created by FyS on 23/05/17.
//

#include <boost/bind.hpp>
#include <iostream>
#include "TcpConnection.hh"

fys::network::TcpConnection::TcpConnection(boost::asio::io_service& io_service) : _isShuttingDown(false), _socket(io_service) {
}

boost::asio::ip::tcp::socket& fys::network::TcpConnection::getSocket() const {
    return _socket;
}

void fys::network::TcpConnection::send(const fys::network::Message&) {

}

void fys::network::TcpConnection::handleWrite(const boost::system::error_code &error, size_t bytesTransferred) {
    if (error || _isShuttingDown)
        shuttingConnectionDown();
}

void fys::network::TcpConnection::handleRead(const boost::system::error_code &error, size_t bytesTransferred) {
    if (!error && !_isShuttingDown) {
        Message message(_buffer);
        readOnSocket();
    }
    else
        shuttingConnectionDown();

}

void fys::network::TcpConnection::readOnSocket() {
_socket.async_read_some(boost::asio::buffer(_buffer, BUFFER_SIZE),
    boost::bind(&TcpConnection::handleRead, shared_from_this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
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
