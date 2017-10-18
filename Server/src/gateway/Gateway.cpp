//
// Created by FyS on 23/05/17.
//

#include <Babble.hh>
#include <Gateway.hh>

fys::gateway::Gateway::~Gateway() = default;

fys::gateway::Gateway::Gateway(const fys::gateway::Context &ctx, boost::asio::io_service &ios, fys::mq::FysBus<fys::network::Message, BUS_QUEUES_SIZE>::ptr &fysBus) :
        _ios(ios),
        _acceptorPlayer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ctx.getPort())),
        _acceptorServer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ctx.getServerPort())),
        _fysBus(fysBus),
        _gamerConnections(1000),
        _serverConnections(10)
{}

void fys::gateway::Gateway::handlePlayerConnection(fys::network::TcpConnection::ptr &newSession) {
    newSession->readOnSocket(_fysBus);
    _gamerConnections.addConnection(newSession);
    runPlayerAccept();
}

void fys::gateway::Gateway::runPlayerAccept() {
    network::TcpConnection::ptr session = network::TcpConnection::create(_ios);

    _acceptorPlayer.async_accept(session->getSocket(), boost::bind(&Gateway::handlePlayerConnection, this, session));
}

void fys::gateway::Gateway::handleServerConnection(fys::network::TcpConnection::ptr &newSession) {
    newSession->readOnSocket(_fysBus);
    _serverConnections.addConnection(newSession);
    std::cout << "coucou"<<std::endl;
    runServerAccept();
}

void fys::gateway::Gateway::runServerAccept() {
    network::TcpConnection::ptr session = network::TcpConnection::create(_ios);

    _acceptorServer.async_accept(session->getSocket(), boost::bind(&Gateway::handleServerConnection, this, session));
}

const fys::network::SessionManager *fys::gateway::Gateway::getGamerConnectionsPointer() const {
    return &_gamerConnections;
}

const fys::network::SessionManager *fys::gateway::Gateway::getServerConnectionsPointer() const {
    return &_serverConnections;
}
