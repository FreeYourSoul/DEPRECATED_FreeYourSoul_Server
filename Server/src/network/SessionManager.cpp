//
// Created by FyS on 30/05/17.
//

#include "SessionManager.hh"

fys::network::SessionManager::~SessionManager() {}

fys::network::SessionManager::SessionManager(const u_int size) : _connectionsActiveToken(size), _connectionsActive(size), _connectionsPending(size)
{}

void fys::network::SessionManager::addPendingConnection(fys::network::TcpConnection::ptr &newConnection) {
    _connectionsPending.push_back(newConnection);
}

