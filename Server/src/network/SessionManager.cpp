//
// Created by FyS on 30/05/17.
//

#include <spdlog/spdlog.h>
#include <TokenGenerator.hh>
#include <TcpConnection.hh>
#include <FySMessage.pb.h>
#include "SessionManager.hh"

fys::network::SessionManager::SessionManager(const uint size) : _connections(size), _connectionsToken(size)
{}

uint fys::network::SessionManager::addConnection(const fys::network::TcpConnection::ptr &newConnection) {
    uint i = 0;

    for (; i < _connections.size(); ++i) {
        if (!_connections.at(i)) {
            connectionHandle(newConnection, i);
            return i;
        }
    }
    _connections.resize(_connections.size() + 1000, nullptr);
    _connectionsToken.resize(_connections.size() + 1000);
    connectionHandle(newConnection, i);
    return i;
}

void fys::network::SessionManager::connectionHandle(const fys::network::TcpConnection::ptr &newConnection, const uint i) {
    Token newToken = fys::utils::TokenGenerator::getInstance()->generateByte();

    this->_connections.at(i) = newConnection;
    this->_connectionsToken.at(i) = newToken;
    newConnection->setSessionIndex(i);
    newConnection->setCustomShutdownHandler([this, i, token = std::move(newToken)]() { this->disconnectUser(i, token); });
}

void fys::network::SessionManager::disconnectUser(const uint idxSession, const fys::network::Token &token) {
    if (idxSession < _connectionsToken.size()) {
        if (std::equal(_connectionsToken.at(idxSession).begin(), _connectionsToken.at(idxSession).end(), token.begin())) {
            spdlog::get("c")->debug("Disconnect user {} from Session manager ({}) and token {}", idxSession, _name, std::string(token.begin(), token.end()));
            _connections.at(idxSession) = nullptr;
            _connectionsToken.at(idxSession) = {};
            return;
        }
    }
    spdlog::get("c")->error("Couldn't find the specified user's token to disconnect on session manager {}", _name);
}

const std::string fys::network::SessionManager::getConnectionToken(const uint indexInSession) const noexcept {
    if (indexInSession < _connectionsToken.size())
        return std::string(_connectionsToken.at(indexInSession).begin(), _connectionsToken.at(indexInSession).end());
    return "";
}

void fys::network::SessionManager::sendResponse(const uint indexInSession, fys::pb::FySResponseMessage &&msg) const noexcept {
    if (indexInSession < _connections.size())
        _connections.at(indexInSession)->send(std::move(msg));
}

void fys::network::SessionManager::send(const uint indexInSession, fys::pb::FySMessage &&msg) const noexcept {
    if (indexInSession < _connections.size())
        _connections.at(indexInSession)->send(std::move(msg));
}

std::pair<std::string, ushort> fys::network::SessionManager::getConnectionData(const uint idxInSession) const noexcept {
    if (idxInSession >= _connections.size() || !_connections.at(idxInSession))
        return std::make_pair(std::string(""), static_cast<ushort>(0));
    return std::make_pair(_connections.at(idxInSession)->getIpAddress(), _connections.at(idxInSession)->getPort());
}

void fys::network::SessionManager::setName(std::string &&name) {
    _name = std::move(name);
}
