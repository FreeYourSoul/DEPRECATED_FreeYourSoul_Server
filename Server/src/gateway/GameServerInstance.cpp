//
// Created by FyS on 28/08/17.
//

#include "GameServerInstance.hh"

fys::gateway::GameServerInstance::GameServerInstance(fys::gateway::GameServerInstance &&other) noexcept :
_ip(std::move(other._ip)), _port(other._port)
{}

fys::gateway::GameServerInstance &fys::gateway::GameServerInstance::operator=(fys::gateway::GameServerInstance other) {
    std::swap(_ip, other._ip);
    std::swap(_port, other._port);
    return *this;
}

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
