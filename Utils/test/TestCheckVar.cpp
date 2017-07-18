//
// Created by FyS on 16/06/17.
//

#include <boost/test/unit_test.hpp>
#include "../src/CheckVars.hh"

/**
 * ------------------------------------------------------
 *  Bus Initialisation test------------------------------
 * ------------------------------------------------------
 */

BOOST_AUTO_TEST_CASE( test_check_int )
{
    BOOST_CHECK(!fys::utils::Var::check(-1));
    BOOST_CHECK(fys::utils::Var::check(1));
}

BOOST_AUTO_TEST_CASE( test_check_string )
{
    BOOST_CHECK(fys::utils::Var::check(std::string("okok")));
    BOOST_CHECK(!fys::utils::Var::check(std::string("")));
}

BOOST_AUTO_TEST_CASE( test_check_both )
{
    BOOST_CHECK(!fys::utils::Var::check(std::string("kok"), 111, 22, std::string("")));
    BOOST_CHECK(!fys::utils::Var::check(std::string("ook"), 111, -1, std::string("okok")));
    BOOST_CHECK(fys::utils::Var::check(std::string("ok"), 111, 22, std::string("okok")));
}


