//
// Created by FyS on 23/05/17.
//

#include <Babble.hh>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

fys::gateway::Gateway::~Gateway() = default;

fys::gateway::Gateway::Gateway(const fys::gateway::Context &ctx, boost::asio::io_service &ios, fys::mq::FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>::ptr &fysBus) :
        _ios(ios),
        _acceptorPlayer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ctx.getPort())),
        _acceptorServer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ctx.getServerPort())),
        _fysBus(fysBus),
        _gamerConnections(1000),
        _serverConnections(10)
{}

void fys::gateway::Gateway::runPlayerAccept() {
    const network::TcpConnection::ptr session = network::TcpConnection::create(_ios);

    _acceptorPlayer.async_accept(session->getSocket(),

            [this, session](const boost::system::error_code& e) {
                session->readOnSocket(_fysBus);
                this->_gamerConnections.addConnection(session);
                this->runPlayerAccept();
            }

    );
}

void fys::gateway::Gateway::runServerAccept() {
    const network::TcpConnection::ptr session = network::TcpConnection::create(_ios);

    _acceptorServer.async_accept(session->getSocket(),

            [this, session](const boost::system::error_code& e) {
                session->readOnSocket(_fysBus);
                _serverConnections.addConnection(session);
                this->runServerAccept();
            }

    );
}

const fys::network::SessionManager &fys::gateway::Gateway::getGamerConnections() const {
    return _gamerConnections;
}

const fys::network::SessionManager &fys::gateway::Gateway::getServerConnections() const {
    return _serverConnections;
}

void fys::gateway::Gateway::addGameServer(const uint indexInSession) {
    GameServerInstance instance;
    auto [ip, port] = _serverConnections.getConnectionData(indexInSession);
    instance.setIp(ip);
    instance.setPort(port);
}

void fys::gateway::Gateway::setAuthServer(const uint indexInSession) {
    auto [ip, port] = _serverConnections.getConnectionData(indexInSession);
    _authServer.setIp(ip);
    _authServer.setPort(port);
}

bool fys::gateway::Gateway::isAuthServerSet() const {
//     return _authServer.getPort() > 0 && !_authServer.getIp().empty();
    return true;
}

#pragma clang diagnostic pop