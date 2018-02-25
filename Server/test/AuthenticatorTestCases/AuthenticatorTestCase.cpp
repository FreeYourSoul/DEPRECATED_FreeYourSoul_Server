//
// Created by FyS on 21/01/18.
//

#define BOOST_TEST_MODULE authenticator_testcase

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <Authenticator.hh>

struct mockFixture {
    mockFixture() {
        BOOST_TEST_MESSAGE("setup fixture");
        auto bus = std::make_shared<fys::mq::FysBus<fys::pb::FySMessage, fys::gateway::BUS_QUEUES_SIZE> > (fys::pb::Type_ARRAYSIZE);
        boost::asio::io_service ios;
        gtwMock = fys::gateway::Gateway::create({}, ios, bus);
    }
    ~mockFixture() {
        BOOST_TEST_MESSAGE("teardown fixture");
    }

    fys::gateway::Gateway::ptr gtwMock;

};

BOOST_FIXTURE_TEST_SUITE(correctTestSuite, mockFixture)

    BOOST_FIXTURE_TEST_CASE( test_auth_player, mockFixture ) {
        fys::gateway::buslistener::Authenticator auth(gtwMock);
        std::cout << "THE TEST THAT MAKE ME CRAZY" << std::endl;
        assert(true);
    }

BOOST_AUTO_TEST_SUITE_END()