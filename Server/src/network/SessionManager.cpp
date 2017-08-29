//
// Created by FyS on 30/05/17.
//

#include "SessionManager.hh"

fys::network::SessionManager::~SessionManager() {}

fys::network::SessionManager::SessionManager()
{
}

void fys::network::SessionManager::addPendingConnection(fys::network::TcpConnection::pointer &newConnection) {
    _connectionsPending.push_back(newConnection);
}

