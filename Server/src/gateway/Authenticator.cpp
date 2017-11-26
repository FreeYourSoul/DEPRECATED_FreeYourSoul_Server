//
// Created by FyS on 31/08/17.
//

#include <FySAuthenticationResponse.pb.h>
#include "Authenticator.hh"

fys::gateway::buslistener::Authenticator::Authenticator(Gateway::ptr& gtw) : _gtw(gtw)
{}

void fys::gateway::buslistener::Authenticator::operator()(mq::QueueContainer<pb::FySMessage> msg) {
    pb::LoginMessage authMessage;

    msg.getContained().content().UnpackTo(&authMessage);
    if (pb::LoginMessage_Type_IsValid(authMessage.typemessage())) {
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
    pb::LoginGameServer loginServer;
    pb::FySResponseMessage resp;

    loginMessage.content().UnpackTo(&loginServer);
    if (!_gtw->isAuthServerSet() && loginServer.isworldserver()) {
        // TODO manage error case
        std::cerr << "Error Auth Server not authenticated yet: islogingServer " << std::boolalpha << loginServer.isworldserver() << std::endl;
        return;
    }
    // TODO check on auth server if server has the good magicKey
    std::cout << "Show loginServer message " << loginServer.ShortDebugString() << std::endl;
    pb::AuthenticationResponse detail;
    detail.set_token(_gtw->getServerConnections().getConnectionToken(indexSession));
    resp.set_type(pb::BABBLE);
    resp.set_isok(true);
    resp.mutable_content()->PackFrom(detail);
    std::cout << "TOKEN in authGameServer  : " << detail.token() << std::endl;
    if (!detail.token().empty()) {
        if (loginServer.isworldserver())
            _gtw->addGameServer(indexSession);
        else
            _gtw->setAuthServer(indexSession);
        _gtw->getServerConnections().sendResponse(indexSession, std::move(resp));
    }
}

void fys::gateway::buslistener::Authenticator::authPlayer(uint indexSession, pb::LoginMessage &&loginMessage) {
    if (!_gtw->isAuthServerSet()) {
        // TODO Manage error case
        return;
    }
    pb::LoginPlayerOnGateway loginPlayer;

    loginMessage.content().UnpackTo(&loginPlayer);
    // TODO on auth server if login/password

}

void fys::gateway::buslistener::Authenticator::authAuthServer(uint indexSession, pb::LoginMessage &&loginMessage) {

}

