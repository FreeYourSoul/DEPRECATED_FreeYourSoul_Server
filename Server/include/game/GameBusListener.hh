//
// Created by FyS on 25/05/17.
//

#ifndef FREESOULS_GAMEBUSLISTENER_HH
#define FREESOULS_GAMEBUSLISTENER_HH

#include <IBusListener.hh>

namespace fys {
    namespace gateway {

        class GameBusListener : fys::mq::IBusListener {

        public:
            ~GameBusListener();
            GameBusListener();

            void listen();
            void setBusRoutingKey(const u_int);

        private:
            u_int routingKey;

        };

    }
}


#endif //FREESOULS_GAMEBUSLISTENER_HH
