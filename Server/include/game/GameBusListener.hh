//
// Created by FyS on 25/05/17.
//

#ifndef FREESOULS_GAMEBUSLISTENER_HH
#define FREESOULS_GAMEBUSLISTENER_HH

#include <IBusListener.hh>
#include <Gateway.hh>

namespace fys {
    namespace gateway {

        class GameBusListener : fys::mq::IBusListener<mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE>> {

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
