//
// Created by FyS on 31/08/17.
//

#include <FySLoginMessage.pb.h>
#include <FySAuthenticationResponse.pb.h>
#include "Authenticator.hh"

fys::gateway::buslistener::Authenticator::~Authenticator() {}

fys::gateway::buslistener::Authenticator::Authenticator(const network::SessionManager * const serverSession,
                                                        const network::SessionManager * const playerSession)
        : _serverSessions(serverSession), _playerSessions(playerSession)
{}

void fys::gateway::buslistener::Authenticator::operator()(mq::QueueContainer<pb::FySGtwMessage> msg) {
    pb::LoginMessage authMessage;

    msg.getContained().content().UnpackTo(&authMessage);
    if (pb::FySGtwMessage_Type_IsValid(authMessage.typemessage())) {
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
}

void fys::gateway::buslistener::Authenticator::authGameServer(uint indexSession, pb::LoginMessage &&loginMessage) {
    pb::LoginGameServer gameServer;
    pb::FySGtwResponseMessage resp;

    loginMessage.content().UnpackTo(&gameServer);
    // TODO check if server has the good magicKey
    pb::AuthenticationResponse detail;
    detail.set_token(_serverSessions->getConnectionToken(indexSession));
    resp.set_isok(true);
    resp.mutable_content()->PackFrom(detail);
    std::cout << "TOKEN in authGameServer  : " << detail.token() << std::endl;
    if (!detail.token().empty())
        _serverSessions->sendResponse(indexSession, std::move(resp));
}

void fys::gateway::buslistener::Authenticator::authPlayer(uint indexSession, pb::LoginMessage &&loginMessage) {

}

void fys::gateway::buslistener::Authenticator::authAuthServer(uint indexSession, pb::LoginMessage &&loginMessage) {

}

