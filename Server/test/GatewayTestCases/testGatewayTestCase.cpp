//
// Created by FyS on 01/03/18.
//

#include <catch.hpp>
#include <Gateway.hh>
#include "../mock/MockVerifier.hpp"
#include "../mock/MockData.hpp"

std::unique_ptr<FSeam::MockVerifier> FSeam::MockVerifier::inst = nullptr;

TEST_CASE( "Gateway tests" ) {

    fys::network::SessionManager *gamerSessionManagerMock;
    fys::network::SessionManager *serverSessionManagerMock;
    fys::gateway::Gateway::ptr gtw;

    auto bus = std::make_shared<fys::mq::FysBus<fys::pb::FySMessage, fys::gateway::BUS_QUEUES_SIZE> > (fys::pb::Type_ARRAYSIZE);
    boost::asio::io_service ios;

    gtw = fys::gateway::Gateway::create({}, ios, bus);
    serverSessionManagerMock = const_cast<fys::network::SessionManager *>(&gtw->getServerConnections());

    std::pair<std::string, ushort> pair = std::make_pair(std::string("127.0.0.1"), static_cast<ushort>(4242));
    std::pair<std::string, ushort> *returnPair = &pair;
    FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->dupeMethod("SessionManager", "getConnectionData", [returnPair](void *arg){
        auto *data = static_cast<FSeam::SessionManagerData *>(arg);
        data->getConnectionData_Ret = returnPair;
    });

    SECTION( "Gateway isGameServerInstancesHasPositionId true" ) {

    }
}