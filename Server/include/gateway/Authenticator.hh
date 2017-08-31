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
                ~Authenticator();
                Authenticator(Gateway * const);

                void operator()(const network::Message &);

            private:
                Gateway *_gtw;


            };

        }
    }
}


#endif //FREESOULS_AUTHENTICATION_HH
