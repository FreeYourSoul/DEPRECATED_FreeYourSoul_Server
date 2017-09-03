//
// Created by FyS on 03/07/17.
//

#include "BabbleMessage.hh"
#include "../../../Utils/src/CheckVars.hh"

fys::network::BabbleMessage::~BabbleMessage() {}

fys::network::BabbleMessage::BabbleMessage() {
}

bool fys::network::BabbleMessage::initializeBabbleLogin(Message &msg) {
    msg.byteToString(_author);
    return fys::utils::Var::check(_author);
}

bool fys::network::BabbleMessage::initializeBabbleLogout(Message &msg) {
    msg.byteToString(_author);
    return fys::utils::Var::check(_author);
}

bool fys::network::BabbleMessage::initializeBabbleMessage(Message &msg) {
    _isWhisper = (msg.getOpCode() == WHISPER);
    msg.byteToString(_author);
    msg.byteToString(_addressee);
    msg.byteToString(_content);
    return fys::utils::Var::check(_author, _addressee, _content);
}

const std::string &fys::network::BabbleMessage::getAuthor() const {
    return _author;
}

const std::string &fys::network::BabbleMessage::getMessage() const {
    return _content;
}

const std::string &fys::network::BabbleMessage::getPassword() const {
    return _content;
}

const std::string &fys::network::BabbleMessage::getAddresse() const {
    return _addressee;
}

bool fys::network::BabbleMessage::isWhisper() const {
    return _isWhisper;
}
