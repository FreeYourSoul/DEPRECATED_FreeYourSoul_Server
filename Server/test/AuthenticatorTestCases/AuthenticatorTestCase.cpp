//
// Created by FyS on 21/01/18.
//

#define BOOST_TEST_MODULE authenticator_testcase

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <Authenticator.hh>
#include "../mock/MockVerifier.hpp"

std::unique_ptr<FSeam::MockVerifier> FSeam::MockVerifier::inst = nullptr;
std::once_flag  FSeam::MockVerifier::once_flag = {};

struct mockFixture {
    mockFixture() {
        auto bus = std::make_shared<fys::mq::FysBus<fys::pb::FySMessage, fys::gateway::BUS_QUEUES_SIZE> > (fys::pb::Type_ARRAYSIZE);
        boost::asio::io_service ios;

        gtwMock = fys::gateway::Gateway::create({}, ios, bus);
        FSeam::MockVerifier::instance().getMock(gtwMock.get())->dupeMethod("Gateway", "constructor", [this](void *ptr) {
            std::cout << "duped has been called" << std::endl;
        });
        BOOST_TEST_MESSAGE("setup fixture");
    }
    ~mockFixture() {
        BOOST_TEST_MESSAGE("teardown fixture");
    }

    fys::gateway::Gateway::ptr gtwMock;

};

BOOST_FIXTURE_TEST_SUITE(correctTestSuite, mockFixture)

    BOOST_FIXTURE_TEST_CASE( test_auth_player, mockFixture ) {
        gtwMock->runPlayerAccept();
//        fys::gateway::buslistener::Authenticator auth(gtwMock);
//        fys::pb::FySMessage fm;
//        fys::pb::LoginMessage loginMsg;
//        fys::pb::LoginGameServer gameServerMessage;
//
//        gameServerMessage.set_isworldserver(true);
//        gameServerMessage.set_magicpassword("magie magie");
//        loginMsg.set_typemessage(fys::pb::LoginMessage_Type_LoginGameServer);
//        loginMsg.mutable_content()->PackFrom(gameServerMessage);
//        fm.set_type(fys::pb::AUTH);
//        fm.mutable_content()->PackFrom(loginMsg);
//        fys::mq::QueueContainer<fys::pb::FySMessage> msg(fm);
//        msg.setIndexSession(0);
//        auth(msg);
//        BOOST_CHECK(FSeam::verif(gtwMock.get(), "Gateway", "", 1));
    }

BOOST_AUTO_TEST_SUITE_END()