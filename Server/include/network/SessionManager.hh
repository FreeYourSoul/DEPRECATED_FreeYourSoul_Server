//
// Created by FyS on 30/05/17.
//

#ifndef FREESOULS_CONNECTIONMANAGER_HH
#define FREESOULS_CONNECTIONMANAGER_HH

#include <list>
#include "TcpConnection.hh"

namespace fys {
    namespace network {

        class SessionManager {

        public:
            ~SessionManager();
            SessionManager(const u_int size);

            void addPendingConnection(TcpConnection::ptr &newConnection);

        private:
            std::vector<fys::network::TcpConnection::ptr> _connectionsPending;
            std::vector<std::string> _connectionsActiveToken;
            std::vector<fys::network::TcpConnection::ptr> _connectionsActive;

        };

    }
}


#endif //FREESOULS_CONNECTIONMANAGER_HH
