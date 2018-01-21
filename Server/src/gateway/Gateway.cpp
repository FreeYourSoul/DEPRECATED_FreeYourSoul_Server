//
// Created by FyS on 23/05/17.
//

#include <Babble.hh>
#include <Authenticator.hh>
#include <BusListener.hh>

void fys::gateway::Gateway::start(const Context& ctx) {
    using namespace fys::mq;
    using namespace fys::gateway;
    using namespace fys::network;

    using BabbleBusListener = BusListener <buslistener::Babble, FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>>;
    using AuthBusListener = BusListener <buslistener::Authenticator, FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>>;

    try {
        boost::asio::io_service ios;
        boost::asio::io_service::work work(ios);
        auto fysBus = std::make_shared<FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE> > (fys::pb::Type_ARRAYSIZE);
        Gateway::ptr gtw = Gateway::create(ctx, ios, fysBus);
        buslistener::Babble babble(gtw);
        buslistener::Authenticator authenticator(gtw);
        BabbleBusListener babbleListener(babble);
        AuthBusListener authenticatorListener(authenticator);

        authenticatorListener.launchListenThread(fysBus);
        babbleListener.launchListenThread(fysBus);
        std::cout << ctx << std::endl;
        gtw->runPlayerAccept();
        gtw->runServerAccept();
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

fys::gateway::Gateway::Gateway(const fys::gateway::Context &ctx,
                               boost::asio::io_service &ios,
                               fys::mq::FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>::ptr &fysBus) :
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
                _serverConnections.addConnection(session);
                session->readOnSocket(_fysBus);
                this->runServerAccept();
            }

    );
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

const fys::gateway::GameServerInstance &fys::gateway::Gateway::getServerForAuthenticatedUser(const uint xPos, const uint yPos) {
    for (const GameServerInstance& serverInstance: _gameServers)
        if (serverInstance(xPos, yPos))
            return serverInstance;
    return {};
}
