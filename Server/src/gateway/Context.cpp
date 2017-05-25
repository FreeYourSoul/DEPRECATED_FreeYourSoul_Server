//
// Created by FyS on 26/05/17.
//

#include "Context.hh"

short fys::gateway::Context::getPort() const {
    return port;
}

void fys::gateway::Context::setPort(const short port) {
    Context::port = port;
}

const std::string &fys::gateway::Context::getBusIniFilePath() const {
    return busIniFilePath;
}

void fys::gateway::Context::setBusIniFilePath(const std::string &busIniFilePath) {
    Context::busIniFilePath = busIniFilePath;
}

size_t fys::gateway::Context::getAsioThread() const {
    return asioThread;
}

void fys::gateway::Context::setAsioThread(const size_t asioThread) {
    Context::asioThread = asioThread;
}
