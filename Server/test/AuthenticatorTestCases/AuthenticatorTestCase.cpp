//
// Created by FyS on 21/01/18.
//

#define BOOST_TEST_MODULE authenticator_testcase

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <Authenticator.hh>
#include "../mock/MockVerifier.hpp"
#include "../mock/MockData.hpp"

std::unique_ptr<FSeam::MockVerifier> FSeam::MockVerifier::inst = nullptr;

struct mockFixture {

    mockFixture() {
        auto bus = std::make_shared<fys::mq::FysBus<fys::pb::FySMessage, fys::gateway::BUS_QUEUES_SIZE> > (fys::pb::Type_ARRAYSIZE);
        boost::asio::io_service ios;
        fys::network::SessionManager tmpMock(0);

        gtwMock = fys::gateway::Gateway::create({}, ios, bus);
        gtwMock->setGamerConnections(tmpMock);
        serverSessionManagerMock = const_cast<fys::network::SessionManager *>(&gtwMock->getServerConnections());
        gamerSessionManagerMock = const_cast<fys::network::SessionManager *>(&gtwMock->getGamerConnections());
        BOOST_TEST_MESSAGE("setup fixture");
    }
    ~mockFixture() {
        FSeam::MockVerifier::cleanUp();
        BOOST_TEST_MESSAGE("teardown fixture");
    }

    fys::network::SessionManager *gamerSessionManagerMock;
    fys::network::SessionManager *serverSessionManagerMock;
    fys::gateway::Gateway::ptr gtwMock;

};

BOOST_FIXTURE_TEST_SUITE(correctTestSuite, mockFixture)

    BOOST_FIXTURE_TEST_CASE( test_auth_authserver, mockFixture ) {
        // Mock initialization
        std::shared_ptr<std::string> returnValue = std::make_shared<std::string>("Token");
        FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->dupeMethod("SessionManager", "getConnectionToken", [returnValue](void *ptr) {
            auto *data = static_cast<FSeam::SessionManagerData *>(ptr);
            data->getConnectionToken_Ret = returnValue.get();
        });

        // Launch test
        fys::gateway::buslistener::Authenticator auth(gtwMock);
        fys::pb::FySMessage fm;
        fys::pb::LoginMessage loginMsg;
        fys::pb::LoginGameServer gameServerMessage;

        gameServerMessage.set_isworldserver(false);
        gameServerMessage.set_magicpassword("magie magie");
        loginMsg.set_typemessage(fys::pb::LoginMessage_Type_LoginGameServer);
        loginMsg.mutable_content()->PackFrom(gameServerMessage);
        fm.set_type(fys::pb::AUTH);
        fm.mutable_content()->PackFrom(loginMsg);
        fys::mq::QueueContainer<fys::pb::FySMessage> msg(fm);
        msg.setIndexSession(0);
        auth(msg);

        //Testing assertion
        BOOST_CHECK(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "addGameServer", 0));
        BOOST_CHECK(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "setAuthServer", 1));
        BOOST_CHECK(FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->verify("SessionManager", "sendResponse", 1));
    }

    /**
     * Test authentication call for a server is working
     */
    BOOST_FIXTURE_TEST_CASE( test_auth_server, mockFixture ) {
        // Mock initialization
        std::shared_ptr<std::string> returnValue = std::make_shared<std::string>("Token");
        FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->dupeMethod("SessionManager", "getConnectionToken", [returnValue](void *ptr) {
            auto *data = static_cast<FSeam::SessionManagerData *>(ptr);
            data->getConnectionToken_Ret = returnValue.get();
        });

        // Launch test
        fys::gateway::buslistener::Authenticator auth(gtwMock);
        fys::pb::FySMessage fm;
        fys::pb::LoginMessage loginMsg;
        fys::pb::LoginGameServer gameServerMessage;

        gameServerMessage.set_isworldserver(true);
        gameServerMessage.set_magicpassword("magie magie");
        loginMsg.set_typemessage(fys::pb::LoginMessage_Type_LoginGameServer);
        loginMsg.mutable_content()->PackFrom(gameServerMessage);
        fm.set_type(fys::pb::AUTH);
        fm.mutable_content()->PackFrom(loginMsg);
        fys::mq::QueueContainer<fys::pb::FySMessage> msg(fm);
        msg.setIndexSession(0);
        auth(msg);

        //Testing assertion
        BOOST_CHECK(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "addGameServer", 1));
        BOOST_CHECK(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "setAuthServer", 0));
        BOOST_CHECK(FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->verify("SessionManager", "sendResponse", 1));
    }


BOOST_AUTO_TEST_SUITE_END()