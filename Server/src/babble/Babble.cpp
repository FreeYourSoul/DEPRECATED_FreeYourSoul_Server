//
// Created by FyS on 24/06/17.
//

#include <BabbleMessage.hh>

fys::gateway::buslistener::Babble::~Babble() {}

fys::gateway::buslistener::Babble::Babble(const network::SessionManager * const playerSessions) : _playerSessions(playerSessions) {
    _basicChannels.push_back("Default");
}

void fys::gateway::buslistener::Babble::operator()(fys::mq::QueueContainer<fys::network::Message> *msg) {
    network::BabbleMessage babbleMessage;

    switch (msg->getOpCodeMsg()) {
        case network::BabbleMessage::SEND:
            if (babbleMessage.initializeBabbleMessage(msg->getContained()));
                sendMessage(babbleMessage);
            break;

        case network::BabbleMessage::WHISPER:
            if (babbleMessage.initializeBabbleMessage(msg->getContained()));
                whisperMessage(babbleMessage);
            break;

        case network::BabbleMessage::LOGIN:
            if (babbleMessage.initializeBabbleLogin(msg->getContained()));
                signInOnBabble(babbleMessage);
            break;

        case network::BabbleMessage::SIGNOUT:
            if (babbleMessage.initializeBabbleLogout(msg->getContained()));
                signOutFromBabble(babbleMessage);
            break;

        default:
            break;
    }
    std::cout << "author:" << babbleMessage.getAuthor() << "  message:" << babbleMessage.getMessage() << "  getAddressee:" << babbleMessage.getAddresse()<< std::endl;
}

void fys::gateway::buslistener::Babble::signInOnBabble(const fys::network::BabbleMessage &babbleMessage) {
    std::string tokenSignIn = babbleMessage.getAuthor();

    std::cout << "User Login in Babble" << std::endl;
    if (!tokenSignIn.empty()) {
//        std::list<std::string> &playerConnected = _mapPlayerChannels.at("Default");
//
//        if (!isPlayerConnectedTo(playerConnected, tokenSignIn))
//            playerConnected.push_back(tokenSignIn);
    }
}

void fys::gateway::buslistener::Babble::signOutFromBabble(const fys::network::BabbleMessage &babbleMessage) {
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

bool fys::gateway::buslistener::Babble::isPlayerConnectedTo(const std::list<std::string> &playerConnected, const std::string &player) {
    for (auto it = playerConnected.begin(); it != playerConnected.end(); ++it)
        if (!it->compare(player))
            return true;
    return false;
}

void fys::gateway::buslistener::Babble::sendMessage(const fys::network::BabbleMessage &babbleMessage) {
    std::cout << "User sendMessage in Babble" << std::endl;
}

void fys::gateway::buslistener::Babble::whisperMessage(const fys::network::BabbleMessage &babbleMessage) {
    std::cout << "User whisperMessage in Babble" << std::endl;
}
