//
// Created by FyS on 25/05/17.
//

#ifndef FREESOULS_AUTHBUSLISTENER_HH
#define FREESOULS_AUTHBUSLISTENER_HH

#include <sys/types.h>
#include <IBusListener.hh>

namespace fys {
    namespace gateway {

        class AuthBusListener : fys::mq::IBusListener {

        public:
            ~AuthBusListener();
            AuthBusListener();

            void listen();
            void setBusRoutingKey(const u_int);

        private:
            u_int routingKey;

        };


    }
}


#endif //FREESOULS_AUTHBUSLISTENER_HH
