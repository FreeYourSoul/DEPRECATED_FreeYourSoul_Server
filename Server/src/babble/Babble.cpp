//
// Created by FyS on 24/06/17.
//

#include "../../include/babble/Babble.hh"

fys::gateway::Babble::~Babble() {}

fys::gateway::Babble::Babble(const network::SessionManager *playerSessions) : _playerSessions(playerSessions) {}

void fys::gateway::Babble::signInOnBabble(const std::string &tokenSignIn) {
    std::cout << "User Login in Babble" << std::endl;
}

void fys::gateway::Babble::signOutFromBabble(const std::string &tokenSignOut) {
    std::cout << "User signOutFromBabble in Babble" << std::endl;

}

void fys::gateway::Babble::sendMessage(const fys::network::Message &babbleMessage) const {
    std::cout << "User sendMessage in Babble" << std::endl;

}

void fys::gateway::Babble::whisperMessage(const fys::network::Message message) const {
    std::cout << "User whisperMessage in Babble" << std::endl;

}
