//
// Created by FyS on 21/01/18.
//

#ifndef FREESOULS_GATEWAY_HPP
#define FREESOULS_GATEWAY_HPP

#include <SessionManager.hh>
#include "FySMock.hpp"

namespace fys::gateway {

    class Gateway : public testing::Mock {

    public:
        void addGameServer(uint, const std::string &string) {
            addCallFor("addGameServer");
        }

        void setAuthServer(const uint) {
            addCallFor("setAuthServer");
        }

        const GameServerInstance &getServerForAuthenticatedUser(const std::string &v) {
            addCallFor("getServerForAuthenticatedUser");
            return mockReturnGetServerForAuthenticatedUser;
        }

        bool isAuthServerSet() const {
            addCallFor("isAuthServerSet");
            return mockReturnIsAuthServerSet;
        }

        const network::SessionManager &getGamerConnections() const {
            addCallFor("getGamerConnections");
            return mockReturnGetGamerConnections;
        }

        const network::SessionManager &getServerConnections() const {
            addCallFor("getServerConnections");
            return mockReturnGetServerConnections;
        }


    public:
        GameServerInstance mockReturnGetServerForAuthenticatedUser;
        network::SessionManager mockReturnGetGamerConnections;
        network::SessionManager mockReturnGetServerConnections;
        bool mockReturnIsAuthServerSet;

    };

}

#endif //FREESOULS_GATEWAY_HPP
