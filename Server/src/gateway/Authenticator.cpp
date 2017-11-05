//
// Created by FyS on 31/08/17.
//

#include <FySLoginMessage.pb.h>
#include "Authenticator.hh"

fys::gateway::buslistener::Authenticator::~Authenticator() {}

fys::gateway::buslistener::Authenticator::Authenticator(const network::SessionManager * const serverSession) : _serverSessions(serverSession)
{}

void fys::gateway::buslistener::Authenticator::operator()(mq::QueueContainer<pb::FySGtwMessage> msg) {
    pb::LoginMessage authMessage;

    msg.getContained().content().UnpackTo(&authMessage);
    switch (authMessage.typemessage()) {
        case pb::LoginMessage_Type_LoginPlayerOnGateway :
            authPlayer(msg.getIndexSession(), std::move(authMessage));
            break;

        case pb::LoginMessage_Type_LoginGameServer:
            authGameServer(msg.getIndexSession(), std::move(authMessage));
            break;

        case pb::LoginMessage_Type_LoginAuthServer:
            authAuthServer(msg.getIndexSession(), std::move(authMessage));
            break;

        default:
            break;
    }
}

void fys::gateway::buslistener::Authenticator::authGameServer(uint indexSession, pb::LoginMessage &&loginMessage) {
    pb::LoginGameServer gameServer;
    loginMessage.content().UnpackTo(&gameServer);
}

void fys::gateway::buslistener::Authenticator::authPlayer(uint indexSession, pb::LoginMessage &&loginMessage) {

}

void fys::gateway::buslistener::Authenticator::authAuthServer(uint indexSession, pb::LoginMessage &&loginMessage) {

}

