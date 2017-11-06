//
// Created by FyS on 23/05/17.
//

#include <boost/asio.hpp>
#include <iostream>
#include <Gateway.hh>
#include <bitset>

fys::network::TcpConnection::TcpConnection(boost::asio::io_service& io_service) : _isShuttingDown(false), _socket(io_service) {
}

boost::asio::ip::tcp::socket& fys::network::TcpConnection::getSocket() {
    return _socket;
}

void fys::network::TcpConnection::send(pb::FySGtwResponseMessage&& msg) {
    boost::asio::streambuf b;
    std::ostream os(&b);
    msg.SerializeToOstream(&os);

    _socket.async_write_some(b.prepare(msg.ByteSizeLong()),
                             [this](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                                 std::cout << "Writting response : " <<  bytes_transferred << std::endl;
                                 if (((boost::asio::error::eof == ec) || (boost::asio::error::connection_reset == ec)) && !_isShuttingDown) {
                                     std::cerr << "An Error Occured during writting" << std::endl;
                                     shuttingConnectionDown();
                                 }
                             }
    );
}

void fys::network::TcpConnection::readOnSocket(fys::mq::FysBus<pb::FySGtwMessage, gateway::BUS_QUEUES_SIZE>::ptr &fysBus) {
    std::fill(_buffer, _buffer + MESSAGE_BUFFER_SIZE, 0);
    _socket.async_read_some(boost::asio::buffer(_buffer, MESSAGE_BUFFER_SIZE),
                            [this, &fysBus](boost::system::error_code ec, const std::size_t byteTransfered) {
                                this->handleRead(ec, byteTransfered, fysBus);
                            });
}

void fys::network::TcpConnection::handleRead(const boost::system::error_code &error, const size_t bytesTransferred,
                                             fys::mq::FysBus<pb::FySGtwMessage, gateway::BUS_QUEUES_SIZE>::ptr fysBus) {
    if (!((boost::asio::error::eof == error) || (boost::asio::error::connection_reset == error)) && !_isShuttingDown) {
        mq::QueueContainer<pb::FySGtwMessage> containerMsg;
        pb::FySGtwMessage message;

        message.ParseFromArray(_buffer, static_cast<int>(bytesTransferred));
        readOnSocket(fysBus);
        containerMsg.setIndexSession(this->_sessionIndex);
        containerMsg.setContained(message);
        containerMsg.setOpCodeMsg(message.type());
        std::cout << "Raw Message to write on bus :" << message.ShortDebugString()  << " container op code : " << containerMsg.getOpCodeMsg() << " bytetransfered : " << bytesTransferred << " with index: " << _sessionIndex << std::endl;
        fysBus->pushInBus(containerMsg);
    }
    else
        shuttingConnectionDown();

}

void fys::network::TcpConnection::shuttingConnectionDown() {
    if (!_isShuttingDown) {
        std::cout << "Shutting down socket connection..." << std::endl;
        _isShuttingDown = true;
        try {
            _customShutdownHandler();
            _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            _socket.close();
        }
        catch (std::exception &) {}
    }
}

uint fys::network::TcpConnection::getSessionIndex() const {
    return _sessionIndex;
}

void fys::network::TcpConnection::setSessionIndex(uint _sessionIndex) {
    TcpConnection::_sessionIndex = _sessionIndex;
}

void fys::network::TcpConnection::setCustomShutdownHandler(const std::function<void()> &customShutdownHandler) {
    TcpConnection::_customShutdownHandler = customShutdownHandler;
}

std::string fys::network::TcpConnection::getIpAddress() const {
    return _socket.remote_endpoint().address().to_string();
}

ushort fys::network::TcpConnection::getPort() const {
    return _socket.remote_endpoint().port();
}
