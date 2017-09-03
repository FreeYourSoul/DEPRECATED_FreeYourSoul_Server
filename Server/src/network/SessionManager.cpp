//
// Created by FyS on 30/05/17.
//

#include <TokenGenerator.hh>
#include "SessionManager.hh"

fys::network::SessionManager::~SessionManager() {}

fys::network::SessionManager::SessionManager(const u_int size) : _connectionsToken(size), _connections(size)
{}

const u_int fys::network::SessionManager::addConnection(const fys::network::TcpConnection::ptr &newConnection) {
    u_int i = 0;

    for (; i < _connections.size(); ++i) {
        if (_connections.at(i)) {
            _connections[i] = newConnection;
            return i;
        }
    }
    _connections.resize(_connections.size() + 1000);
    _connectionsToken.resize(_connections.size() + 1000);
    _connections[i] = newConnection;
    _connectionsToken[i] = fys::utils::TokenGenerator::getInstance()->generateByte();
    return i;
}

void fys::network::SessionManager::disconnectUser(const fys::network::Token &token) {
    u_int i = 0;

    for (; i < _connectionsToken.size(); ++i) {
        if (std::equal(_connectionsToken.at(i).begin(), _connectionsToken.at(i).end(), token.begin())) {
            _connections[i] = nullptr;
            return;
        }
    }
    std::cerr << "Couldn't find the specified user's token to disconnect" << std::endl;
}




