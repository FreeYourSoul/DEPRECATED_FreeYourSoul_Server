//
// Created by FyS on 30/05/17.
//

#include <TokenGenerator.hh>
#include "SessionManager.hh"

fys::network::SessionManager::~SessionManager() {}

fys::network::SessionManager::SessionManager(const u_int size) : _connections(size, nullptr), _connectionsToken(size)
{}

const u_int fys::network::SessionManager::addConnection(const fys::network::TcpConnection::ptr &newConnection) {
    u_int i = 0;
    auto connectionHandle = [this, &newConnection] (int i) {
        Token newToken = fys::utils::TokenGenerator::getInstance()->generateByte();

        this->_connections[i] = newConnection;
        this->_connectionsToken[i] = newToken;
        newConnection->setSessionIndex(i);
        newConnection->setCustomShutdownHandler([this, newToken]() { this->disconnectUser(newToken); });
        std::cout << "index ->" << i <<std::endl;
    };

    for (; i < _connections.size(); ++i) {
        if (!_connections.at(i)) {
            connectionHandle(i);
            return i;
        }
    }
    _connections.resize(_connections.size() + 1000, nullptr);
    _connectionsToken.resize(_connections.size() + 1000);
    connectionHandle(i);
    return i;
}

void fys::network::SessionManager::disconnectUser(const fys::network::Token &token) {
    u_int i = 0;

    for (; i < _connectionsToken.size(); ++i) {
        if (std::equal(_connectionsToken.at(i).begin(), _connectionsToken.at(i).end(), token.begin())) {
            std::cout << "Disconnect user " << i << " from Session manager" << std::endl;
            _connections[i] = nullptr;
            return;
        }
    }
    std::cerr << "Couldn't find the specified user's token to disconnect" << std::endl;
}




