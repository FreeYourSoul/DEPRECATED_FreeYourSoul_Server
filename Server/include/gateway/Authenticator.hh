//
// Created by FyS on 31/08/17.
//

#ifndef FREESOULS_AUTHENTICATION_HH
#define FREESOULS_AUTHENTICATION_HH


#include <Message.hh>
#include <AuthMessage.hh>
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

                void operator()(mq::QueueContainer<network::Message> msg);

            private:
                void authServer(network::AuthMessage &&message);
                void authPlayer(network::AuthMessage &&message);

            private:
                const network::SessionManager *_serverSessions;

            };

        }
    }
}


#endif //FREESOULS_AUTHENTICATION_HH
