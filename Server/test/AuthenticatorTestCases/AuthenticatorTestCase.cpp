//
// Created by FyS on 21/01/18.
//

#define BOOST_TEST_MODULE authenticator_testcase

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <Authenticator.hh>

BOOST_AUTO_TEST_SUITE(correctTestSuite)

    BOOST_AUTO_TEST_CASE( test_auth_player ) {
        auto bus = std::make_shared<fys::mq::FysBus<fys::pb::FySMessage, fys::gateway::BUS_QUEUES_SIZE> > (fys::pb::Type_ARRAYSIZE);
        boost::asio::io_service ios;
        fys::gateway::Gateway::ptr gtw = fys::gateway::Gateway::create({}, ios, bus);

        gtw->runPlayerAccept();
        fys::gateway::buslistener::Authenticator auth(gtw);
        std::cout << "THE TEST THAT MAKE ME CRAZY" << std::endl;
        assert(true);
    }

BOOST_AUTO_TEST_SUITE_END()