//
// Created by FyS on 03/07/17.
//

#include "BabbleMessage.hh"
#include "../../../Utils/src/CheckVars.hh"

fys::network::BabbleMessage::~BabbleMessage() {}

fys::network::BabbleMessage::BabbleMessage() {}

fys::gateway::Babble::funcPtr fys::network::BabbleMessage::initialize(const Message& message) {
    fys::gateway::Babble::funcPtr returnPointerFunc = nullptr;

    switch (message.getOpCode()) {
        case BabbleOpCode::LOGIN:
            initializeBabbleLogin(message);
            if (fys::utils::Var::check(_author))
                returnPointerFunc = &fys::gateway::Babble::signInOnBabble;
            break;

        case BabbleOpCode::SIGNOUT:
            initializeBabbleLogout(message);
            if (fys::utils::Var::check(_author))
                returnPointerFunc = &fys::gateway::Babble::signOutFromBabble;
            break;

        default:
            initializeBabbleMessage(message);
            if (fys::utils::Var::check(_author, _addressee, _content))
                returnPointerFunc = &fys::gateway::Babble::sendMessage;
            break;
    }
    return returnPointerFunc;
}

bool fys::network::BabbleMessage::initializeBabbleLogin(const Message &msg) {
    msg.byteToString(_author, 2);
    return true;
}

bool fys::network::BabbleMessage::initializeBabbleLogout(const Message &msg) {
    std::cout << "okok logout" << std::endl;
    return true;
}

bool fys::network::BabbleMessage::initializeBabbleMessage(const Message &msg) {
    std::cout << "okok Message" << std::endl;
    return true;
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

bool fys::network::BabbleMessage::isLogout() const {
    return _isLogout;
}

bool fys::network::BabbleMessage::isLogin() const {
    return _isLogin;
}

