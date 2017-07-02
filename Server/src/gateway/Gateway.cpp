//
// Created by FyS on 23/05/17.
//

#include <Babble.hh>
#include <thread>
#include <BabbleBusListener.hh>

fys::gateway::Gateway::~Gateway() { }

fys::gateway::Gateway::Gateway(const fys::gateway::Context &ctx, boost::asio::io_service &ios, fys::mq::FysBus<fys::network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr &fysBus) :
        _ios(ios),
        _acceptor(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ctx.getPort())),
        _fysBus(fysBus)
{}

void fys::gateway::Gateway::handlePlayerConnection(fys::network::TcpConnection::pointer &newSession) {
    newSession->readOnSocket(_fysBus);
    _gamerConnections.addPendingConnection(newSession);
    runPlayerAccept();
}

void fys::gateway::Gateway::runPlayerAccept() {
    network::TcpConnection::pointer session = network::TcpConnection::create(_ios);

    _acceptor.async_accept(session->getSocket(), boost::bind(&Gateway::handlePlayerConnection, this, session));
}

const fys::network::SessionManager *fys::gateway::Gateway::getGamerConnectionsPointer() const {
    return &_gamerConnections;
}
