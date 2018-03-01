//
// Created by FyS on 21/01/18.
//

#include <Gateway.hh>
#include "MockVerifier.hpp"
#include "MockData.hpp"

fys::gateway::Gateway::Gateway(const fys::gateway::Context &ctx,
                               boost::asio::io_service &ios,
                               fys::mq::FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>::ptr &fysBus) :
        _ios(ios),
        _acceptorPlayer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1111)),
        _acceptorServer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4222)),
        _fysBus(fysBus),
        _gamerConnections(static_cast<uint>(1000)),
        _serverConnections(static_cast<uint>(10)) {
}

void fys::gateway::Gateway::start(const Context& ctx) {
    std::cout << "Gateway > start called" << std::endl;
}

void fys::gateway::Gateway::runPlayerAccept() {
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("Gateway", __FUNCTION__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("Gateway", __FUNCTION__);
}

void fys::gateway::Gateway::runServerAccept() {
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("Gateway", __FUNCTION__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("Gateway", __FUNCTION__);
}

void fys::gateway::Gateway::addGameServer(uint indexInSession, const std::string &positionId) {
    FSeam::GatewayData data;
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("Gateway", __FUNCTION__, &data);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("Gateway", __FUNCTION__);
}

void fys::gateway::Gateway::setAuthServer(const uint indexInSession) {
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("Gateway", __FUNCTION__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("Gateway", __FUNCTION__);
}

const fys::gateway::GameServerInstance &fys::gateway::Gateway::getServerForAuthenticatedUser(const std::string& positionId) {
    FSeam::GatewayData data;
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("Gateway", __FUNCTION__, &data);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("Gateway", __FUNCTION__);
    return *data.getServerForAuthenticatedUser_Ret;
}

bool fys::gateway::Gateway::isGameServerInstancesHasPositionId(const std::string& positionId) const {
    FSeam::GatewayData data;
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("Gateway", __FUNCTION__, &data);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("Gateway", __FUNCTION__);
    return *data.isGameServerInstancesHasPositionId_Ret;
}