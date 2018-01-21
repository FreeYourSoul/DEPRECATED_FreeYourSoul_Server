//
// Created by FyS on 31/08/17.
//

#include "Authenticator.hh"

fys::gateway::buslistener::Authenticator::Authenticator(Gateway::ptr& gtw) : _gtw(gtw) {}

void fys::gateway::buslistener::Authenticator::operator()(mq::QueueContainer<pb::FySMessage> msg) {
    pb::LoginMessage authMessage;

    msg.getContained().content().UnpackTo(&authMessage);
    if (pb::LoginMessage_Type_IsValid(authMessage.typemessage())) {
        switch (authMessage.typemessage()) {
            case pb::LoginMessage_Type_LoginPlayerOnGateway:
                authPlayer(msg.getIndexSession(), std::move(authMessage));
                break;

            case pb::LoginMessage_Type_LoginGameServer:
                authServer(msg.getIndexSession(), std::move(authMessage));
                break;

            case pb::LoginMessage_Type_LoginAuthServer:
                authServer(msg.getIndexSession(), std::move(authMessage));
                break;

            default:
                break;
        }
    }
}

void fys::gateway::buslistener::Authenticator::authServer(const uint indexSession, pb::LoginMessage &&loginMessage) {
    pb::LoginGameServer loginServer;

    loginMessage.content().UnpackTo(&loginServer);
    if (!_gtw->isAuthServerSet() && loginServer.isworldserver()) {
        sendErrorToServer(indexSession, "Error Auth server not registered",
                          fys::pb::LoginErrorResponse::Type::LoginErrorResponse_Type_AUTH_SERVER_UNAVAILABLE);
        return;
    }
    // TODO check on auth server if server has the good magicKey -> thanks to the PositionId
    std::cout << " Show loginServer message " << loginServer.ShortDebugString() << std::endl << std::endl;
    pb::AuthenticationResponse detail;
    detail.set_token(_gtw->getServerConnections().getConnectionToken(indexSession));
    if (!detail.token().empty()) {
        pb::FySResponseMessage resp;
        resp.set_type(pb::AUTH);
        resp.set_isok(true);
        resp.mutable_content()->PackFrom(detail);
        if (loginServer.isworldserver())
            _gtw->addGameServer(indexSession, loginServer.magicpassword());
        else
            _gtw->setAuthServer(indexSession);
        _gtw->getServerConnections().sendResponse(indexSession, std::move(resp));
    }
}

void fys::gateway::buslistener::Authenticator::authPlayer(uint indexSession, pb::LoginMessage &&loginMessage) {
    if (!_gtw->isAuthServerSet()) {
        sendErrorToPlayer(indexSession, "Error Auth server not registered",
                          fys::pb::LoginErrorResponse::Type::LoginErrorResponse_Type_AUTH_SERVER_UNAVAILABLE);
        return;
    }
    pb::LoginPlayerOnGateway loginPlayer;

    loginMessage.content().UnpackTo(&loginPlayer);
    std::cout << "Show loginPlayer message " << loginPlayer.ShortDebugString() << std::endl;
    // TODO on auth server if login/password

    std::string positionId = "UNIV_1a"; // todo get the good positionId from db
    const fys::gateway::GameServerInstance &gsi = _gtw->getServerForAuthenticatedUser(positionId);
    pb::FySResponseMessage resp;
    pb::AuthenticationResponse detail;
    detail.set_token(_gtw->getServerConnections().getConnectionToken(indexSession));
    detail.set_ip(gsi.getIp());
    detail.set_port(std::to_string(gsi.getPort()));
    resp.set_type(pb::AUTH);
    resp.set_isok(true);
    resp.mutable_content()->PackFrom(detail);
    _gtw->getGamerConnections().sendResponse(indexSession, std::move(resp));
}

void fys::gateway::buslistener::Authenticator::sendErrorToServer(
        const uint indexSession, std::string &&error, fys::pb::LoginErrorResponse::Type errorType) {
    fys::pb::FySResponseMessage resp;
    createErrorMessage(resp, std::move(error), errorType);
    _gtw->getServerConnections().sendResponse(indexSession, std::move(resp));
}

void fys::gateway::buslistener::Authenticator::sendErrorToPlayer(
        const uint indexSession, std::string &&error, fys::pb::LoginErrorResponse::Type errorType) {
    fys::pb::FySResponseMessage resp;
    createErrorMessage(resp, std::move(error), errorType);
    _gtw->getGamerConnections().sendResponse(indexSession, std::move(resp));
}

inline void fys::gateway::buslistener::Authenticator::createErrorMessage(
        fys::pb::FySResponseMessage &resp, std::string &&error, fys::pb::LoginErrorResponse::Type errorType) {
    fys::pb::LoginErrorResponse detail;

    std::cerr << error << std::endl;
    resp.set_isok(false);
    resp.set_type(fys::pb::AUTH);
    detail.set_user("GTW");
    detail.set_typeerror(errorType);
    resp.mutable_content()->PackFrom(detail);
}

