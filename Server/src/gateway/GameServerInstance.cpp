//
// Created by FyS on 28/08/17.
//

#include "GameServerInstance.hh"

fys::gateway::GameServerInstance::~GameServerInstance() {

}

fys::gateway::GameServerInstance::GameServerInstance() {

}

fys::gateway::GameServerInstance::GameServerInstance(const fys::gateway::GameServerInstance &other) :
_ip(other._ip), _port(other._port)
{}

fys::gateway::GameServerInstance::GameServerInstance(fys::gateway::GameServerInstance &&other) :
_ip(std::move(other._ip)), _port(std::move(other._port))
{}

const std::string &fys::gateway::GameServerInstance::getIp() const {
    return _ip;
}

void fys::gateway::GameServerInstance::setIp(const std::string &ip) {
    GameServerInstance::_ip = ip;
}

const std::string &fys::gateway::GameServerInstance::getPort() const {
    return _port;
}

void fys::gateway::GameServerInstance::setPort(const std::string &port) {
    GameServerInstance::_port = port;
}
