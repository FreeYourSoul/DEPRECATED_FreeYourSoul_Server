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
                void authGameServer(pb::LoginMessage &&message);
                void authPlayer(pb::LoginMessage &&message);
                void authAuthServer(pb::LoginMessage &&message);

            private:
                const network::SessionManager *_serverSessions;

            };

        }
    }
}


#endif //FREESOULS_AUTHENTICATION_HH
