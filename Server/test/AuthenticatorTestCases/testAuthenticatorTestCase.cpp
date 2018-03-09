//
// Created by FyS on 01/03/18.
//

#define CATCH_CONFIG_MAIN

#include <spdlog/spdlog.h>
#include <catch.hpp>
#include <Gateway.hh>
#include <Authenticator.hh>
#include <FySMessage.pb.h>
#include <FySAuthenticationLoginMessage.pb.h>
#include "../mock/MockVerifier.hpp"
#include "../mock/MockData.hpp"

std::unique_ptr<FSeam::MockVerifier> FSeam::MockVerifier::inst = nullptr;

TEST_CASE( "AuthenticatorListener tests" ) {
    //logger
    spdlog::drop_all();
    spdlog::set_async_mode(1024, spdlog::async_overflow_policy::discard_log_msg);
    spdlog::set_pattern("[%x %H:%M:%S] [%l] %v");
    std::vector<spdlog::sink_ptr> sinks;
    auto stdout_sink = spdlog::sinks::stdout_sink_mt::instance();
    auto color_sink = std::make_shared<spdlog::sinks::ansicolor_sink>(stdout_sink);
    sinks.push_back(color_sink);
    auto sys_logger = std::make_shared<spdlog::logger>("c", begin(sinks), end(sinks));
    spdlog::register_logger(sys_logger);

    //test
    fys::network::SessionManager *gamerSessionManagerMock;
    fys::network::SessionManager *serverSessionManagerMock;
    fys::gateway::Gateway::ptr gtwMock;

    auto bus = std::make_shared<fys::mq::FysBus<fys::pb::FySMessage, fys::gateway::BUS_QUEUES_SIZE> > (fys::pb::Type_ARRAYSIZE);
    boost::asio::io_service ios;

    gtwMock = fys::gateway::Gateway::create({}, ios, bus);
    serverSessionManagerMock = &gtwMock->getServerConnections();
    gamerSessionManagerMock = &gtwMock->getGamerConnections();

    fys::gateway::buslistener::Authenticator auth(gtwMock);

    SECTION( "Test Authentication bad token" ) {
        // Mock initialization
        FSeam::MockVerifier::cleanUp();
        std::shared_ptr<std::string> returnValue = std::make_shared<std::string>("");
        FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->dupeMethod("SessionManager", "getConnectionToken", [returnValue](void *ptr) {
            auto *data = static_cast<FSeam::SessionManagerData *>(ptr);
            data->getConnectionToken_Ret = returnValue.get();
        });

        // Launch tests
        fys::pb::FySMessage fm;
        fys::pb::LoginMessage loginMsg;
        fys::pb::LoginGameServer gameServerMessage;

        SECTION( "Authentication Game Server bad token" ) {
            // Launch test
            gameServerMessage.set_isworldserver(true);
            gameServerMessage.set_magicpassword("magie magie");
            gameServerMessage.set_portforplayer("33");
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

        SECTION( "Authentication Auth Server bad token" ) {
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

    }

    SECTION( "Test Authentication Server Sucess" ) {
        // Mock initialization
        FSeam::MockVerifier::cleanUp();
        std::shared_ptr<std::string> returnValue = std::make_shared<std::string>("Token");
        FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->dupeMethod("SessionManager", "getConnectionToken", [returnValue](void *ptr) {
            auto *data = static_cast<FSeam::SessionManagerData *>(ptr);
            data->getConnectionToken_Ret = returnValue.get();
        });

        // Launch tests
        fys::pb::FySMessage fm;
        fys::pb::LoginMessage loginMsg;
        fys::pb::LoginGameServer gameServerMessage;

        SECTION ( "Auth Server Authentication Success" ) {
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
            REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "setAuthServer", 1));
            REQUIRE(FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->verify("SessionManager", "sendResponse", 1));
        }

        SECTION( "Game Server Authentication Success" ) {
            gameServerMessage.set_isworldserver(true);
            gameServerMessage.set_magicpassword("magie magie");
            loginMsg.set_typemessage(fys::pb::LoginMessage_Type_LoginAuthServer);
            loginMsg.mutable_content()->PackFrom(gameServerMessage);
            fm.set_type(fys::pb::AUTH);
            fm.mutable_content()->PackFrom(loginMsg);
            fys::mq::QueueContainer<fys::pb::FySMessage> msg(fm);
            msg.setIndexSession(0);
            auth(msg);

            //Testing assertion
            REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "addGameServer", 1));
            REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "setAuthServer", 0));
            REQUIRE(FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->verify("SessionManager", "sendResponse", 1));
        }
    }

    SECTION( "Player Authentication" ) {
        // Mock initialization
        FSeam::MockVerifier::cleanUp();
        std::shared_ptr<std::string> returnValue = std::make_shared<std::string>("Token");
        FSeam::MockVerifier::instance().getMock(gamerSessionManagerMock)->
                dupeMethod("SessionManager", "getConnectionToken", [returnValue](void *ptr) {
            auto *data = static_cast<FSeam::SessionManagerData *>(ptr);
            data->getConnectionToken_Ret = returnValue.get();
        });

        auto returnValuePair = std::make_pair<std::string, ushort>(std::string("ip"), 1322);
        auto *ptrReturnValuePair = &returnValuePair;
        FSeam::MockVerifier::instance().getMock(gamerSessionManagerMock)->
                dupeMethod("SessionManager", "getConnectionData", [ptrReturnValuePair](void *ptr) {
            auto *data = static_cast<FSeam::SessionManagerData *>(ptr);
            data->getConnectionData_Ret = ptrReturnValuePair;
        });

        std::shared_ptr<fys::gateway::GameServerInstance> returnGsi = std::make_shared<fys::gateway::GameServerInstance>();
        FSeam::MockVerifier::instance().getMock(gtwMock.get())->
                dupeMethod("Gateway", "getServerForAuthenticatedUser", [returnGsi](void *ptr) {
            auto *data = static_cast<FSeam::GatewayData *>(ptr);
            data->getServerForAuthenticatedUser_Ret = returnGsi.get();
        });

        // Launch Tests
        fys::pb::FySMessage fm;
        fys::pb::LoginMessage loginMsg;
        fys::pb::LoginPlayerOnGateway playerOnGateway;

        SECTION( "Player authentication Success call" ) {
            // Mock initialization
            bool boolValue = true;
            bool *returnValueBool = &boolValue;
            FSeam::MockVerifier::instance().getMock(gtwMock.get())->
                    dupeMethod("Gateway", "isGameServerInstancesHasPositionId", [returnValueBool](void *arg){
                auto *data = static_cast<FSeam::GatewayData *>(arg);
                data->isGameServerInstancesHasPositionId_Ret = returnValueBool;
            });

            playerOnGateway.set_password("password");
            loginMsg.set_typemessage(fys::pb::LoginMessage_Type_LoginPlayerOnGateway);
            loginMsg.mutable_content()->PackFrom(playerOnGateway);
            fm.set_type(fys::pb::AUTH);
            fm.mutable_content()->PackFrom(loginMsg);
            fys::mq::QueueContainer<fys::pb::FySMessage> msg(fm);
            msg.setIndexSession(0);
            auth(msg);

            //Testing assertion
            REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "getServerForAuthenticatedUser", 1));
            REQUIRE(FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->verify("SessionManager", "getConnectionToken", 0));
            REQUIRE(FSeam::MockVerifier::instance().getMock(gamerSessionManagerMock)->verify("SessionManager", "getConnectionToken", 2));
            REQUIRE(FSeam::MockVerifier::instance().getMock(gamerSessionManagerMock)->verify("SessionManager", "sendResponse", 1));
        }

        SECTION( "Player authentication Success call" ) {
            // Mock initialization
            bool boolValue = false;
            bool *returnValueBool = &boolValue;
            FSeam::MockVerifier::instance().getMock(gtwMock.get())->
                    dupeMethod("Gateway", "isGameServerInstancesHasPositionId", [returnValueBool](void *arg){
                auto *data = static_cast<FSeam::GatewayData *>(arg);
                data->isGameServerInstancesHasPositionId_Ret = returnValueBool;
            });

            playerOnGateway.set_password("password");
            loginMsg.set_typemessage(fys::pb::LoginMessage_Type_LoginPlayerOnGateway);
            loginMsg.mutable_content()->PackFrom(playerOnGateway);
            fm.set_type(fys::pb::AUTH);
            fm.mutable_content()->PackFrom(loginMsg);
            fys::mq::QueueContainer<fys::pb::FySMessage> msg(fm);
            msg.setIndexSession(0);
            auth(msg);

            //Testing assertion
            REQUIRE(FSeam::MockVerifier::instance().getMock(gtwMock.get())->verify("Gateway", "getServerForAuthenticatedUser", 0));
            REQUIRE(FSeam::MockVerifier::instance().getMock(serverSessionManagerMock)->verify("SessionManager", "getConnectionToken", 0));
            REQUIRE(FSeam::MockVerifier::instance().getMock(gamerSessionManagerMock)->verify("SessionManager", "sendResponse", 0));
        }

    }

}