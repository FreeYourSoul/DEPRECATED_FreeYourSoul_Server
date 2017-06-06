//
// Created by FyS on 30/05/17.
//

#include "AnswerForwarder.hh"

fys::network::AnswerForwarder::~AnswerForwarder() {}

fys::network::AnswerForwarder::AnswerForwarder(fys::network::SessionManager &gamersConnections) : _gamersConnections(gamersConnections) {}

void fys::network::AnswerForwarder::forwardMessage(const fys::network::Message &msg, const std::list<std::string> &gamerTokens) const {
    _gamersConnections.
}
