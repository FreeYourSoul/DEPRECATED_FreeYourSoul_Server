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
            enum { CONNECTION_SIZE = 1000};

            std::vector<fys::network::TcpConnection::pointer> _connectionsPending;
            std::vector<std::string> _connectionsActiveToken;
            std::vector<fys::network::TcpConnection::pointer> _connectionsActive;

        };

    }
}


#endif //FREESOULS_CONNECTIONMANAGER_HH
