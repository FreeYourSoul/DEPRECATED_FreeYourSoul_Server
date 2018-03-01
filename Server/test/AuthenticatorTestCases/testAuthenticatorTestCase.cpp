//
// Created by FyS on 01/03/18.
//

#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <Gateway.hh>
#include <Authenticator.hh>
#include "../mock/MockVerifier.hpp"
#include "../mock/MockData.hpp"

std::unique_ptr<FSeam::MockVerifier> FSeam::MockVerifier::inst = nullptr;

TEST_CASE( "AuthenticatorListener tests" ) {

    fys::network::SessionManager *gamerSessionManagerMock;
    fys::network::SessionManager *serverSessionManagerMock;
    fys::gateway::Gateway::ptr gtwMock;

    auto bus = std::make_shared<fys::mq::FysBus<fys::pb::FySMessage, fys::gateway::BUS_QUEUES_SIZE> > (fys::pb::Type_ARRAYSIZE);
    boost::asio::io_service ios;
    fys::network::SessionManager tmpMock(0);

    gtwMock = fys::gateway::Gateway::create({}, ios, bus);
    gtwMock->setGamerConnections(tmpMock);
    serverSessionManagerMock = const_cast<fys::network::SessionManager *>(&gtwMock->getServerConnections());
    gamerSessionManagerMock = const_cast<fys::network::SessionManager *>(&gtwMock->getGamerConnections());


    SECTION( "Test Game Server Authentication" ) {
        FSeam::MockVerifier::cleanUp();

        // Mock initialization
        std::shared_ptr<std::string> returnValue = std::make_shared<std::string>("");
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
        REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "addGameServer", 0));
        REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "setAuthServer", 0));
        REQUIRE(FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->verify("SessionManager", "sendResponse", 0));

    }

    SECTION( "Test Authentication Server Authentication" ) {
        // Mock initialization
        std::shared_ptr<std::string> returnValue = std::make_shared<std::string>("");
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
        loginMsg.set_typemessage(fys::pb::LoginMessage_Type_LoginAuthServer);
        loginMsg.mutable_content()->PackFrom(gameServerMessage);
        fm.set_type(fys::pb::AUTH);
        fm.mutable_content()->PackFrom(loginMsg);
        fys::mq::QueueContainer<fys::pb::FySMessage> msg(fm);
        msg.setIndexSession(0);
        auth(msg);

        //Testing assertion
        REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "addGameServer", 0));
        REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "setAuthServer", 0));
        REQUIRE(FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->verify("SessionManager", "sendResponse", 0));
    }

    SECTION( "Test Game Server Authentication bad token" ) {
        // Mock initialization
        std::shared_ptr<std::string> returnValue = std::make_shared<std::string>("");
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
        REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "addGameServer", 0));
        REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "setAuthServer", 0));
        REQUIRE(FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->verify("SessionManager", "sendResponse", 0));
    }

    SECTION( "Test Authentication Server Authentication bad token" ) {
        // Mock initialization
        std::shared_ptr<std::string> returnValue = std::make_shared<std::string>("");
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
        loginMsg.set_typemessage(fys::pb::LoginMessage_Type_LoginAuthServer);
        loginMsg.mutable_content()->PackFrom(gameServerMessage);
        fm.set_type(fys::pb::AUTH);
        fm.mutable_content()->PackFrom(loginMsg);
        fys::mq::QueueContainer<fys::pb::FySMessage> msg(fm);
        msg.setIndexSession(0);
        auth(msg);

        //Testing assertion
        REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "addGameServer", 0));
        REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "setAuthServer", 0));
        REQUIRE(FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->verify("SessionManager", "sendResponse", 0));
    }

}