//
// Created by FyS on 06/07/17.
//

#include "AuthMessage.hh"

fys::network::AuthMessage::~AuthMessage() {}

fys::network::AuthMessage::AuthMessage() {}

bool fys::network::AuthMessage::initializePlayerAuth(fys::network::Message &msg) {
    return true;
}

bool fys::network::AuthMessage::initializeServerAuth(fys::network::Message &msg) {
    return true;
}

const std::string &fys::network::AuthMessage::get_user() const {
    return _user;
}

const std::string &fys::network::AuthMessage::get_password() const {
    return _password;
}

const std::string &fys::network::AuthMessage::get_token() const {
    return _token;
}

bool fys::network::AuthMessage::isServerAuth() const {
    return _isServerAuth;
}
