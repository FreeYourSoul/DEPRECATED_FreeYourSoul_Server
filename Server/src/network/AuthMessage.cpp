//
// Created by FyS on 06/07/17.
//

#include "AuthMessage.hh"

fys::network::AuthMessage::~AuthMessage() {}

fys::network::AuthMessage::AuthMessage() {}

fys::network::AuthMessage::AuthMessage(const fys::network::AuthMessage &other) :
        _token(other._token), _user(other._user), _password(other._password), _isServerAuth(other._isServerAuth)
{}

fys::network::AuthMessage::AuthMessage(fys::network::AuthMessage &&other) :
        _token(std::move(other._token)), _password(std::move(other._password)),
        _user(std::move(other._user)), _isServerAuth(std::move(other._isServerAuth))
{}

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
