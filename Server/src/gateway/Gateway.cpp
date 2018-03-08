//
// Created by FyS on 23/05/17.
//

#include <spdlog/spdlog.h>
#include <FysBus.hh>
#include <Babble.hh>
#include <BusListener.hh>
#include <TcpConnection.hh>
#include <Authenticator.hh>
#include <FySMessage.pb.h>
#include <Gateway.hh>
#include <boost/lexical_cast.hpp>

void fys::gateway::Gateway::start(const Context& ctx) {
    using namespace fys::mq;
    using namespace fys::gateway;
    using namespace fys::network;

    using BabbleBusListener = BusListener <buslistener::Babble, FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>>;
    using AuthBusListener = BusListener <buslistener::Authenticator, FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>>;

    try {
        boost::asio::io_service ios;
        boost::asio::io_service::work work(ios);
        auto fysBus = std::make_shared<FysBus<fys::pb::FySMessage, fys::gateway::BUS_QUEUES_SIZE> > (fys::pb::Type_ARRAYSIZE);
        Gateway::ptr gtw = Gateway::create(ctx, ios, fysBus);
        buslistener::Babble babble(gtw);
        buslistener::Authenticator authenticator(gtw);
        BabbleBusListener babbleListener(babble);
        AuthBusListener authenticatorListener(authenticator);

        authenticatorListener.launchListenThread(fysBus);
        babbleListener.launchListenThread(fysBus);
        gtw->runPlayerAccept();
        gtw->runServerAccept();
        ios.run();
    }
    catch (std::exception &e) {
        spdlog::get("c")->error("An exception has been thrown at the gateway startup {}", e.what());
    }
}

fys::gateway::Gateway::Gateway(const fys::gateway::Context &ctx,
                               boost::asio::io_service &ios,
                               fys::mq::FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>::ptr &fysBus) :
        _ios(ios),
        _acceptorPlayer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ctx.getPort())),
        _acceptorServer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ctx.getServerPort())),
        _fysBus(fysBus),
        _gamerConnections(static_cast<uint>(1000)),
        _serverConnections(static_cast<uint>(10))
{}

void fys::gateway::Gateway::runPlayerAccept() {
    const network::TcpConnection::ptr session = network::TcpConnection::create(_ios);

    _acceptorPlayer.async_accept(session->getSocket(),

            [this, session](const boost::system::error_code& e) {
                this->_gamerConnections.addConnection(session);
                session->readOnSocket(_fysBus);
                this->runPlayerAccept();
            }

    );
}

void fys::gateway::Gateway::runServerAccept() {
    const network::TcpConnection::ptr session = network::TcpConnection::create(_ios);

    _acceptorServer.async_accept(session->getSocket(),

            [this, session](const boost::system::error_code& e) {
                 //TODO check on DB server if the ip of the current connected client is an accepted server
                this->_serverConnections.addConnection(session);
                session->readOnSocket(_fysBus);
                this->runServerAccept();
            }

    );
}

void fys::gateway::Gateway::addGameServer(uint indexInSession, const std::string &port, const std::string &positionId) {
    GameServerInstance instance;
    [[maybe_unused]]auto [ip, unused_port] = _serverConnections.getConnectionData(indexInSession);

    instance.setIp(ip);
    instance.setPort(boost::lexical_cast<unsigned short>(port));
    instance.setPositionId(positionId);
    instance.setIndexInServerSession(indexInSession);
    spdlog::get("c")->info("A server has been added to the cluster [ip:{} port:{} positionId:{}]", ip, port, positionId);
    _gameServers.push_back(std::move(instance));
}

void fys::gateway::Gateway::setAuthServer(const uint indexInSession) {
    auto [ip, port] = _serverConnections.getConnectionData(indexInSession);
    _authServer.setIp(ip);
    _authServer.setPort(port);
}

const fys::gateway::GameServerInstance &fys::gateway::Gateway::getServerForAuthenticatedUser(const std::string& positionId) {
    for (uint i = 0; i < _gameServers.size(); ++i)
        if (_gameServers.at(i)(positionId))
            return _gameServers.at(i);
    if (!_gameServers.empty())
        return _gameServers.at(0);
    spdlog::get("c")->error("{} error, no gameServer authenticated on the gateway", __FUNCTION__);
    throw std::exception();
}

bool fys::gateway::Gateway::isGameServerInstancesHasPositionId(const std::string& positionId) const {
    if (_gameServers.empty())
        return false;
    for (const GameServerInstance &gsi : _gameServers) {
        if (gsi.getPort() <= 0 || gsi.getIp().empty() || gsi.getIp().empty())
            return false;
    }
    return true;
}
