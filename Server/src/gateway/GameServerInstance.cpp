//
// Created by FyS on 28/08/17.
//

#include "GameServerInstance.hh"

fys::gateway::GameServerInstance::~GameServerInstance() {

}

fys::gateway::GameServerInstance::GameServerInstance() {

}

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
