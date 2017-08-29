//
// Created by FyS on 06/07/17.
//

#include "AuthMessage.hh"


fys::network::AuthMessage::~AuthMessage() {}

fys::network::AuthMessage::AuthMessage() {}

fys::network::http::HttpAuthClient::funcPtr fys::network::AuthMessage::initialize(const fys::network::Message &message) {
    return nullptr;
}

const std::string &fys::network::AuthMessage::get_user() const {
    return _user;
}

void fys::network::AuthMessage::set_user(const std::string &_user) {
    AuthMessage::_user = _user;
}

const std::string &fys::network::AuthMessage::get_password() const {
    return _password;
}

void fys::network::AuthMessage::set_password(const std::string &_password) {
    AuthMessage::_password = _password;
}

const std::string &fys::network::AuthMessage::get_token() const {
    return _token;
}

void fys::network::AuthMessage::set_token(const std::string &_token) {
    AuthMessage::_token = _token;
}
