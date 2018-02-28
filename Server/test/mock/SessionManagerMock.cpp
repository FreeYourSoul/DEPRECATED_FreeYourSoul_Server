//
// Created by FyS on 28/02/18.
//

#include "SessionManager.hh"
#include "MockVerifier.hpp"
#include "MockData.hpp"

fys::network::SessionManager::SessionManager(const uint size) : _connections(size), _connectionsToken(size) {
}

uint fys::network::SessionManager::addConnection(const fys::network::TcpConnection::ptr &newConnection) {
    FSeam::SessionManagerData data;
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __FUNCTION__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __FUNCTION__);
    return *data.addConnection_Ret;
}

void fys::network::SessionManager::connectionHandle(const fys::network::TcpConnection::ptr &newConnection, const uint i) {
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __FUNCTION__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __FUNCTION__);
}

void fys::network::SessionManager::disconnectUser(const fys::network::Token &token) {
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __FUNCTION__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __FUNCTION__);
}

const std::string fys::network::SessionManager::getConnectionToken(const uint indexInSession) const noexcept {
    FSeam::SessionManagerData data;
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __FUNCTION__, &data);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __FUNCTION__);
    return data.getConnectionToken_Ret ? *data.getConnectionToken_Ret : "";
}

void fys::network::SessionManager::sendResponse(uint indexInSession, fys::pb::FySResponseMessage &&message) const noexcept {
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __FUNCTION__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __FUNCTION__);
}

std::pair<std::string, ushort>  fys::network::SessionManager::getConnectionData(const uint indexInSession) const noexcept {
    FSeam::SessionManagerData data;
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __FUNCTION__, &data);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __FUNCTION__);
    return *data.getConnectionData_Ret;
}
