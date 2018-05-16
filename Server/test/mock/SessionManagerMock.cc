//
// Created by FyS on 28/02/18.
//

#include <TcpConnection.hh>
#include "SessionManager.hh"
#include "MockVerifier.hpp"
#include "MockData.hpp"

fys::network::SessionManager::SessionManager(uint size) : _connections(size), _connectionsToken(size) {
}

uint fys::network::SessionManager::addConnection(const fys::network::TcpConnection::ptr &newConnection) {
    FSeam::SessionManagerData data;
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __func__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __func__);
    return *data.addConnection_Ret;
}

void fys::network::SessionManager::connectionHandle(const fys::network::TcpConnection::ptr &newConnection, uint i) {
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __func__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __func__);
}

void fys::network::SessionManager::disconnectUser(uint indexInSession, const fys::network::Token &token) {
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __func__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __func__);
}

const std::string fys::network::SessionManager::getConnectionToken(uint indexInSession) const noexcept {
    FSeam::SessionManagerData data;
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __func__, &data);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __func__);
    return data.getConnectionToken_Ret ? *data.getConnectionToken_Ret : "";
}

void fys::network::SessionManager::sendResponse(uint indexInSession, fys::pb::FySResponseMessage &&msg) const noexcept {
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __func__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __func__);
}

void fys::network::SessionManager::send(uint indexInSession, fys::pb::FySMessage &&msg) const noexcept {
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __func__);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __func__);
}

std::pair<std::string, ushort>  fys::network::SessionManager::getConnectionData(uint indexInSession) const noexcept {
    FSeam::SessionManagerData data;
    FSeam::MockVerifier::instance().getMock(this)->invokeDupedMethod("SessionManager", __func__, &data);
    FSeam::MockVerifier::instance().getMock(this)->methodCall("SessionManager", __func__);
    return *data.getConnectionData_Ret;
}
