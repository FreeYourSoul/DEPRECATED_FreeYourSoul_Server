//
// Created by FyS on 31/08/17.
//

#ifndef FREESOULS_AUTHENTICATION_HH
#define FREESOULS_AUTHENTICATION_HH

#include <FySLoginMessage.pb.h>
#include "Gateway.hh"

namespace fys {
    namespace gateway {
        namespace buslistener {

            class Authenticator {

            public:
                enum { IndexInBus = 0 };

            public:
                ~Authenticator();
                Authenticator(const network::SessionManager * const serverSession);

                void operator()(mq::QueueContainer<pb::FySGtwMessage> msg);

            private:
                void authGameServer(uint indexSession, pb::LoginMessage &&loginMessage);
                void authPlayer(uint indexSession, pb::LoginMessage &&loginMessage);
                void authAuthServer(uint indexSession, pb::LoginMessage &&loginMessage);

            private:
                const network::SessionManager *_serverSessions;
                const network::SessionManager *_playerSessions;
            };

        }
    }
}


#endif //FREESOULS_AUTHENTICATION_HH
