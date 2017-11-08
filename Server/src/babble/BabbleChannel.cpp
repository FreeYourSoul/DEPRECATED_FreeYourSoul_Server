//
// Created by FyS on 24/06/17.
//

#include <algorithm>
#include "BabbleChannel.hh"

void fys::gateway::BabbleChannel::connectOnChannel(const std::string &addedConnect) {
    if (!addedConnect.empty() && std::find(_connectedOnChannel.begin(), _connectedOnChannel.end(), addedConnect) == _connectedOnChannel.end())
        _connectedOnChannel.push_back(addedConnect);
}

void fys::gateway::BabbleChannel::disconnectFromChannel(const std::string &disconnect) {
    _connectedOnChannel.remove(disconnect);
}

const std::list<std::string> &fys::gateway::BabbleChannel::getConnectedOnChannel() const {
    return _connectedOnChannel;
}

