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
            SessionManager();

            void addPendingConnection(TcpConnection::pointer &newConnection);

        private:
            std::list<fys::network::TcpConnection::pointer> _connectionsPending;
            std::map<std::string, fys::network::TcpConnection::pointer> _connectionsActive;

        };

    }
}


#endif //FREESOULS_CONNECTIONMANAGER_HH
