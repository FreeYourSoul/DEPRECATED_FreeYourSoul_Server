//
// Created by FyS on 30/05/17.
//

#include <TokenGenerator.hh>
#include "SessionManager.hh"

fys::network::SessionManager::SessionManager(const u_int size) : _connections(size), _connectionsToken(size)
{}

const u_int fys::network::SessionManager::addConnection(const fys::network::TcpConnection::ptr &newConnection) {
    u_int i = 0;

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
    newConnection->setCustomShutdownHandler([this, newToken]() { this->disconnectUser(newToken); });
    std::cout << "index ->" << i <<std::endl;
}

void fys::network::SessionManager::disconnectUser(const fys::network::Token &token) {
    u_int i = 0;

    for (; i < _connectionsToken.size(); ++i) {
        if (std::equal(_connectionsToken.at(i).begin(), _connectionsToken.at(i).end(), token.begin())) {
            std::cout << "Disconnect user " << i << " from Session manager" << std::endl;
            _connections.at(i) = nullptr;
            return;
        }
    }
    std::cerr << "Couldn't find the specified user's token to disconnect" << std::endl;
}

std::string fys::network::SessionManager::getConnectionToken(const uint indexInSession) const noexcept {
    if (indexInSession < _connectionsToken.size())
        return std::string(_connectionsToken.at(indexInSession).begin(), _connectionsToken.at(indexInSession).end());
    return "";
}

void fys::network::SessionManager::sendResponse(uint indexInSession, fys::pb::FySGtwResponseMessage &&message) const noexcept {
    if (indexInSession < _connections.size())
        _connections.at(indexInSession)->send(std::move(message));
}

std::pair<std::string, ushort>  fys::network::SessionManager::getConnectionData(const uint indexInSession) const noexcept {
    return std::make_pair(_connections.at(indexInSession)->getIpAddress(), _connections.at(indexInSession)->getPort());
}




