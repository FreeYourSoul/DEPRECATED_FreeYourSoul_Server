//
// Created by FyS on 31/08/17.
//

#include <AuthMessage.hh>
#include "Authenticator.hh"

fys::gateway::buslistener::Authenticator::~Authenticator() {}

fys::gateway::buslistener::Authenticator::Authenticator(const network::SessionManager * const serverSession) : _serverSessions(serverSession)
{}

void fys::gateway::buslistener::Authenticator::operator()(mq::QueueContainer<network::Message> *msg) {
    network::AuthMessage authMessage;

    switch (msg->getOpCodeMsg()) {
        case network::AuthMessage::AUTH_PLAYER:
            authMessage.initializePlayerAuth(msg->getContained());
            authPlayer(std::move(authMessage));
            break;

        case network::AuthMessage::AUTH_SERVER:
            authMessage.initializeServerAuth(msg->getContained());
            authServer(std::move(authMessage));
            break;

        default:
            break;
    }
}

void fys::gateway::buslistener::Authenticator::authServer(fys::network::AuthMessage &&message) {

}

void fys::gateway::buslistener::Authenticator::authPlayer(fys::network::AuthMessage &&message) {

}

