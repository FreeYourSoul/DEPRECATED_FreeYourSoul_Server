//
// Created by FyS on 03/09/17.
//

#include <iostream>
#include <boost/lexical_cast.hpp>
#include "TokenGenerator.hh"

fys::utils::TokenGenerator *fys::utils::TokenGenerator::instance = nullptr;

const std::string fys::utils::TokenGenerator::generate() const {
    return boost::lexical_cast<std::string>((const_cast<TokenGenerator *>(this))->_generator());
}

const std::vector<char> fys::utils::TokenGenerator::generateByte() {
    boost::uuids::uuid u = _generator();
    std::vector<char> v(u.size());
    std::copy(u.begin(), u.end(), v.begin());
    return v;
}

