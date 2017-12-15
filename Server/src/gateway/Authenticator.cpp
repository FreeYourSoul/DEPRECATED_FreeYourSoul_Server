//
// Created by FyS on 31/08/17.
//

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

    loginMessage.content().UnpackTo(&loginServer);
    if (!_gtw->isAuthServerSet() && loginServer.isworldserver()) {
        sendError(indexSession, "Error", fys::pb::LoginErrorResponse::Type::LoginErrorResponse_Type_AUTH_SERVER_UNAVAILABLE);
        return;
    }
    pb::FySResponseMessage resp;
    // TODO check on auth server if server has the good magicKey
    std::cout << "Show loginServer message " << loginServer.ShortDebugString() << std::endl;
    pb::AuthenticationResponse detail;
    detail.set_token(_gtw->getServerConnections().getConnectionToken(indexSession));
    resp.set_type(pb::AUTH);
    resp.set_isok(true);
    resp.mutable_content()->PackFrom(detail);
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

void fys::gateway::buslistener::Authenticator::sendError(
        const uint indexSession, std::string&& error, fys::pb::LoginErrorResponse::Type errorType) {
    fys::pb::FySResponseMessage resp;
    fys::pb::LoginErrorResponse detail;

    std::cerr << error << std::endl;
    resp.set_isok(false);
    resp.set_type(fys::pb::AUTH);
    detail.set_user("GTW");
    detail.set_typeerror(errorType);
    resp.mutable_content()->PackFrom(detail);
    _gtw->getServerConnections().sendResponse(indexSession, std::move(resp));
}

