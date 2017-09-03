//
// Created by FyS on 30/05/17.
//

#ifndef FREESOULS_CONNECTIONMANAGER_HH
#define FREESOULS_CONNECTIONMANAGER_HH

#include <zconf.h>
#include <list>
#include "TcpConnection.hh"

namespace fys {
    namespace network {
        using Token = std::vector<char>;

        class SessionManager {

        public:
            ~SessionManager();
            SessionManager(const u_int size);

            const u_int addConnection(const TcpConnection::ptr &newConnection);
            void disconnectUser(const Token &);

        private:
            std::vector<fys::network::TcpConnection::ptr> _connections;
            std::vector<Token > _connectionsToken;
        };

    }
}


#endif //FREESOULS_CONNECTIONMANAGER_HH
