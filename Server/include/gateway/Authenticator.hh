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

                ~Authenticator();
                Authenticator(const Gateway::ptr&);

                void operator()(mq::QueueContainer<pb::FySGtwMessage> msg);

            private:
                void authGameServer(const uint indexSession, pb::LoginMessage &&loginMessage);
                void authPlayer(const uint indexSession, pb::LoginMessage &&loginMessage);
                void authAuthServer(const uint indexSession, pb::LoginMessage &&loginMessage);

            private:
                const Gateway::ptr _gtw;
            };

        }
    }
}


#endif //FREESOULS_AUTHENTICATION_HH
