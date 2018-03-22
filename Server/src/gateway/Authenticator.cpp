//
// Created by FyS on 31/08/17.
//

#include <spdlog/spdlog.h>
#include <Gateway.hh>
#include <QueueContainer.hh>
#include <FySAuthenticationLoginMessage.pb.h>
#include <FySMessage.pb.h>
#include <TokenGenerator.hh>
#include "ServerMagicExtractor.hh"
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

void fys::gateway::buslistener::Authenticator::authServer(uint indexSession, pb::LoginMessage &&loginMessage) {
    pb::LoginGameServer loginServer;

    loginMessage.content().UnpackTo(&loginServer);
    if (!_gtw->isAuthServerSet() && loginServer.isworldserver()) {
        sendErrorToServer(indexSession, "Error Auth server not registered",
                          fys::pb::LoginErrorResponse::Type::LoginErrorResponse_Type_AUTH_SERVER_UNAVAILABLE);
        return;
    }
    ServerMagicExtractor sme(loginServer.magicpassword());
    // TODO check on auth server if server has the good magicKey -> thanks to the PositionId
    spdlog::get("c")->debug("Show loginServer message: " + loginServer.ShortDebugString());
    pb::AuthenticationResponse detail;
    detail.set_token(_gtw->getServerConnections().getConnectionToken(indexSession));
    if (!detail.token().empty()) {
        pb::FySResponseMessage resp;

        resp.set_type(pb::AUTH);
        resp.set_isok(true);
        resp.mutable_content()->PackFrom(detail);
        if (loginServer.isworldserver())
            _gtw->addGameServer(indexSession, loginServer.portforplayer(), sme.getPositionId());
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
    spdlog::get("c")->debug("Show loginPlayer message: {}", loginPlayer.ShortDebugString());
    // TODO on auth server if login/password
    std::string positionId = "UNIV_1a"; // todo get the good positionId from db
    if ("password" == loginPlayer.password()) {
        if (!positionId.empty() && _gtw->isGameServerInstancesHasPositionId(positionId)) {
            const fys::gateway::GameServerInstance &gsi = _gtw->getServerForAuthenticatedUser(positionId);

            _gtw->getGamerConnections().sendResponse(indexSession, std::move(getAuthPlayerResponse(indexSession, gsi)));
            _gtw->getServerConnections().send(gsi.getIndexInServerSession(), std::move(getNotifNewPlayerMessage(indexSession, std::move(loginMessage))));
        }
    }
    else {
        spdlog::get("c")->warn("Bad login/password");
    }
}

fys::pb::FySMessage fys::gateway::buslistener::Authenticator::getNotifNewPlayerMessage(uint indexSession,
                                                             fys::pb::LoginMessage &&loginMessage) const {
    fys::pb::FySMessage notif;
    fys::pb::LoginMessage loginNotifToServer;
    fys::pb::NotifyPlayerIncoming playerIncoming;

    auto[ip, port] = this->_gtw->getGamerConnections().getConnectionData(indexSession);
    playerIncoming.set_ip(ip);
    playerIncoming.set_token(this->_gtw->getGamerConnections().getConnectionToken(indexSession));
    loginNotifToServer.set_typemessage(fys::pb::LoginMessage_Type_NotifyNewPlayer);
    loginNotifToServer.set_user(loginMessage.user());
    loginNotifToServer.mutable_content()->PackFrom(playerIncoming);
    notif.set_type(fys::pb::AUTH);
    notif.mutable_content()->PackFrom(loginNotifToServer);
    return notif;
}

fys::pb::FySResponseMessage
fys::gateway::buslistener::Authenticator::getAuthPlayerResponse(uint indexSession,
                                                                const fys::gateway::GameServerInstance &gsi) const {
    fys::pb::FySResponseMessage resp;
    fys::pb::AuthenticationResponse detail;

    detail.set_token(this->_gtw->getGamerConnections().getConnectionToken(indexSession));
    detail.set_ip(gsi.getIp());
    detail.set_port(std::to_string(gsi.getPort()));
    resp.set_type(fys::pb::AUTH);
    resp.set_isok(true);
    resp.mutable_content()->PackFrom(detail);
    return resp;
}

void fys::gateway::buslistener::Authenticator::sendErrorToServer(
        uint indexSession, std::string &&error, fys::pb::LoginErrorResponse::Type errorType) {
    fys::pb::FySResponseMessage resp;
    createErrorMessage(resp, std::move(error), errorType);
    _gtw->getServerConnections().sendResponse(indexSession, std::move(resp));
}

void fys::gateway::buslistener::Authenticator::sendErrorToPlayer(
        uint indexSession, std::string &&error, fys::pb::LoginErrorResponse::Type errorType) {
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

