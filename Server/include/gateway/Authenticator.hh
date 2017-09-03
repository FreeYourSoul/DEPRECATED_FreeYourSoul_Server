//
// Created by FyS on 31/08/17.
//

#ifndef FREESOULS_AUTHENTICATION_HH
#define FREESOULS_AUTHENTICATION_HH


#include <Message.hh>
#include "Gateway.hh"

namespace fys {
    namespace gateway {
        namespace buslistener {

            class Authenticator {

            public:
                enum { IndexInBus = 0 };

            public:
                ~Authenticator();
                Authenticator(const Gateway::ptr);

                void operator()(mq::QueueContainer<network::Message> *msg);

            private:
                void authServer(const network::AuthMessage &message);
                void authPlayer(const network::AuthMessage &message);

            private:
                Gateway::ptr _gtw;

            };

        }
    }
}


#endif //FREESOULS_AUTHENTICATION_HH
