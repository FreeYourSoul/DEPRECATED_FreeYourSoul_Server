//
// Created by FyS on 03/07/17.
//

#include "BabbleMessage.hh"

fys::network::BabbleMessage::~BabbleMessage() {}

fys::network::BabbleMessage::BabbleMessage() {}

fys::gateway::Babble::funcPtr fys::network::BabbleMessage::initialize(const Message& message) const {
    return &fys::gateway::Babble::sendMessage;
}

void fys::network::BabbleMessage::initializeBabbleLogin() {

}

void fys::network::BabbleMessage::initializeBabbleLogout() {

}

void fys::network::BabbleMessage::initializeBabbleMessage() {
}

const std::string &fys::network::BabbleMessage::getAuthor() const {
    return _author;
}

const std::string &fys::network::BabbleMessage::getMessage() const {
    return _message;
}

const std::string &fys::network::BabbleMessage::getAddresse() const {
    return _addresse;
}

bool fys::network::BabbleMessage::isWhisper() const {
    return _isWhisper;
}

bool fys::network::BabbleMessage::isLogout() const {
    return _isLogout;
}

bool fys::network::BabbleMessage::isLogin() const {
    return _isLogin;
}

