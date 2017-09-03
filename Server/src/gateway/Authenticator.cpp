//
// Created by FyS on 31/08/17.
//

#include <AuthMessage.hh>
#include "Authenticator.hh"

fys::gateway::buslistener::Authenticator::~Authenticator() {}

fys::gateway::buslistener::Authenticator::Authenticator(Gateway::ptr gtw) : _gtw(gtw)
{}

void fys::gateway::buslistener::Authenticator::operator()(mq::QueueContainer<network::Message> *msg) {
    network::AuthMessage authMessage;

    switch (msg->getOpCodeMsg()) {
        case network::AuthMessage::AUTH_PLAYER:
            authMessage.initializePlayerAuth(msg->getContained());
            authPlayer(authMessage);
            break;

        case network::AuthMessage::AUTH_SERVER:
            authMessage.initializeServerAuth(msg->getContained());
            authServer(authMessage);
            break;
    }
}

void fys::gateway::buslistener::Authenticator::authServer(const fys::network::AuthMessage &message) {
    
}

void fys::gateway::buslistener::Authenticator::authPlayer(const fys::network::AuthMessage &message) {

}

