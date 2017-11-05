//
// Created by FyS on 23/05/17.
//

#include <Babble.hh>
#include <Gateway.hh>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

fys::gateway::Gateway::~Gateway() = default;

fys::gateway::Gateway::Gateway(const fys::gateway::Context &ctx, boost::asio::io_service &ios, fys::mq::FysBus<fys::pb::FySGtwMessage, BUS_QUEUES_SIZE>::ptr &fysBus) :
        _ios(ios),
        _acceptorPlayer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ctx.getPort())),
        _acceptorServer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ctx.getServerPort())),
        _fysBus(fysBus),
        _gamerConnections(1000),
        _serverConnections(10)
{}

void fys::gateway::Gateway::runPlayerAccept() {
    network::TcpConnection::ptr session = network::TcpConnection::create(_ios);

    _acceptorPlayer.async_accept(session->getSocket(),

            [this, session](const boost::system::error_code& e) {
                session->readOnSocket(_fysBus);
                this->_gamerConnections.addConnection(session);
                this->runPlayerAccept();
            }

    );
}

void fys::gateway::Gateway::runServerAccept() {
    network::TcpConnection::ptr session = network::TcpConnection::create(_ios);

    _acceptorServer.async_accept(session->getSocket(),

            [this, session](const boost::system::error_code& e) {
                session->readOnSocket(_fysBus);
                _serverConnections.addConnection(session);
                std::cout << "coucou"<<std::endl;
                this->runServerAccept();
            }

    );
}

const fys::network::SessionManager *fys::gateway::Gateway::getGamerConnectionsPointer() const {
    return &_gamerConnections;
}

const fys::network::SessionManager *fys::gateway::Gateway::getServerConnectionsPointer() const {
    return &_serverConnections;
}

#pragma clang diagnostic pop