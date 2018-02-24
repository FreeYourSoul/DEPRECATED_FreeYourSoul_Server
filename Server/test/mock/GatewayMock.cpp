//
// Created by FyS on 21/01/18.
//

#ifndef FREESOULS_GATEWAY_HPP
#define FREESOULS_GATEWAY_HPP

#include <Gateway.hh>

fys::gateway::Gateway::Gateway(const fys::gateway::Context &ctx,
                               boost::asio::io_service &ios,
                               fys::mq::FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>::ptr &fysBus) :
        _ios(ios),
        _acceptorPlayer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1111)),
        _acceptorServer(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4222)),
        _fysBus(fysBus),
        _gamerConnections(static_cast<uint>(1000)),
        _serverConnections(static_cast<uint>(10))
{}

void fys::gateway::Gateway::start(const Context& ctx) {
    std::cout << "Gateway > start called" << std::endl;
}

void fys::gateway::Gateway::runPlayerAccept() {
    std::cout << "Gateway > runPlayerAccept called"<<std::endl;
}

void fys::gateway::Gateway::runServerAccept() {
    std::cout << "Gateway > runServerAccept called"<<std::endl;
}

void fys::gateway::Gateway::addGameServer(uint indexInSession, const std::string &positionId) {
    std::cout << "Gateway > addGameServer called"<<std::endl;
}

void fys::gateway::Gateway::setAuthServer(const uint indexInSession) {
    std::cout << "Gateway > runServerAccept called"<<std::endl;
}

const fys::gateway::GameServerInstance &fys::gateway::Gateway::getServerForAuthenticatedUser(const std::string& positionId) {
    std::cout << "Gateway > getServerForAuthenticatedUser called"<<std::endl;
}

#endif //FREESOULS_GATEWAY_HPP
