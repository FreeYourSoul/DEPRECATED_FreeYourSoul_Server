//
// Created by FyS on 28/08/17.
//

#include "GameServerInstance.hh"

const std::string &fys::gateway::GameServerInstance::getIp() const {
    return _ip;
}

void fys::gateway::GameServerInstance::setIp(const std::string &ip) {
    GameServerInstance::_ip = ip;
}

ushort fys::gateway::GameServerInstance::getPort() const {
    return _port;
}

void fys::gateway::GameServerInstance::setPort(const ushort port) {
    GameServerInstance::_port = port;
}

bool fys::gateway::GameServerInstance::operator()(const std::string &) const noexcept {
    return false;
}

void fys::gateway::GameServerInstance::setPositionId(const std::string &postionId) {
    _positionId = postionId;
}

const std::string &fys::gateway::GameServerInstance::getPositionId() const {
    return _positionId;
}
