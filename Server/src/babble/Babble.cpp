//
// Created by FyS on 24/06/17.
//

#include <BabbleMessage.hh>

fys::gateway::Babble::~Babble() {}

fys::gateway::Babble::Babble(const network::SessionManager *playerSessions) : _playerSessions(playerSessions) {
    _basicChannels.push_back("Default");
}

void fys::gateway::Babble::signInOnBabble(const fys::network::BabbleMessage &babbleMessage) {
    std::string tokenSignIn = babbleMessage.getAuthor();

    std::cout << "User Login in Babble" << std::endl;
    if (!tokenSignIn.empty()) {
//        std::list<std::string> &playerConnected = _mapPlayerChannels.at("Default");
//
//        if (!isPlayerConnectedTo(playerConnected, tokenSignIn))
//            playerConnected.push_back(tokenSignIn);
    }
}

void fys::gateway::Babble::signOutFromBabble(const fys::network::BabbleMessage &babbleMessage) {
    std::string tokenSignOut = babbleMessage.getAuthor();
    std::string channel = babbleMessage.getAddresse();

    std::cout << "User signOutFromBabble in Babble" << std::endl;
    if (!tokenSignOut.empty()) {
        if (!channel.empty()) {
            std::list<std::string> &playerConnected = _mapPlayerChannels.at(channel);

            if (!isPlayerConnectedTo(playerConnected, tokenSignOut))
                playerConnected.remove(channel);
        }
        else {
            for (auto &x: _mapPlayerChannels) {
                if (!isPlayerConnectedTo(x.second, tokenSignOut))
                    x.second.remove(channel);
            }
        }
    }
}

bool fys::gateway::Babble::isPlayerConnectedTo(std::list<std::string> &playerConnected, const std::string &player) {
    for (std::list<std::string>::iterator it = playerConnected.begin(); it != playerConnected.end(); ++it)
        if (!(*it).compare(player))
            return true;
    return false;
}

void fys::gateway::Babble::sendMessage(const fys::network::BabbleMessage &babbleMessage) {
    std::cout << "User sendMessage in Babble" << std::endl;

}

void fys::gateway::Babble::whisperMessage(const fys::network::BabbleMessage &babbleMessage) {
    std::cout << "User whisperMessage in Babble" << std::endl;

}
