//
// Created by FyS on 24/06/17.
//

#include <Babble.hh>

fys::gateway::buslistener::Babble::Babble(Gateway::ptr &gtw) : _gtw(gtw) {
    _basicChannels.emplace_back("Default");
}

void fys::gateway::buslistener::Babble::operator()(fys::mq::QueueContainer<fys::pb::FySMessage> msg) {

}

void fys::gateway::buslistener::Babble::signInOnBabble(fys::pb::FySBabbleMessage &&babbleMessage) {
}

void fys::gateway::buslistener::Babble::signOutFromBabble(fys::pb::FySBabbleMessage &&babbleMessage) {
    std::cout << "User signOutFromBabble in Babble" << std::endl;
    if (!babbleMessage.token().empty()) {
        if (babbleMessage.iswhisper()) {
            std::list<std::string> &playerConnected = _mapPlayerChannels.at(babbleMessage.content().dest());

            if (!isPlayerConnectedTo(playerConnected, babbleMessage.token()))
                playerConnected.remove(babbleMessage.content().dest());
        }
        else {
            for (auto &x: _mapPlayerChannels) {
                if (!isPlayerConnectedTo(x.second, babbleMessage.token()))
                    x.second.remove(babbleMessage.content().dest());
            }
        }
    }
}

bool fys::gateway::buslistener::Babble::isPlayerConnectedTo(const std::list<std::string> &playerConnected, const std::string &player) {
    for (const auto &it : playerConnected)
        if (it != player)
            return true;
    return false;
}

void fys::gateway::buslistener::Babble::sendMessage(fys::pb::FySBabbleMessage &&babbleMessage) {
    std::cout << "User sendMessage in Babble" << std::endl;
}

void fys::gateway::buslistener::Babble::whisperMessage(fys::pb::FySBabbleMessage &&babbleMessage) {
    std::cout << "User whisperMessage in Babble" << std::endl;
}
