//
// Created by FyS on 31/08/17.
//

#ifndef FREESOULS_AUTHENTICATION_HH
#define FREESOULS_AUTHENTICATION_HH

#include <FySGtwMessage.pb.h>
#include <FySAuthenticationLoginMessage.pb.h>
#include "Gateway.hh"

namespace fys {
    namespace gateway {
        namespace buslistener {

            class Authenticator {

            public:
                enum { IndexInBus = 0 };

                explicit Authenticator(Gateway::ptr&);

                void operator()(mq::QueueContainer<fys::pb::FySGtwMessage> msg);

            private:
                void authGameServer(const uint indexSession, pb::LoginMessage &&loginMessage);
                void authPlayer(const uint indexSession, pb::LoginMessage &&loginMessage);
                void authAuthServer(const uint indexSession, pb::LoginMessage &&loginMessage);

            private:
                Gateway::ptr _gtw;
            };

        }
    }
}


#endif //FREESOULS_AUTHENTICATION_HH
