//
// Created by FyS on 25/05/17.
//

#ifndef FREESOULS_FIGHTBUSLISTENER_HH
#define FREESOULS_FIGHTBUSLISTENER_HH

#include <IBusListener.hh>

namespace fys {
    namespace gateway {

        class FightBusListener : fys::mq::IBusListener {

        public:
            ~FightBusListener();
            FightBusListener();

            void listen();
            void setBusRoutingKey(const u_int);

        private:
            u_int routingKey;

        };

    }
}


#endif //FREESOULS_FIGHTBUSLISTENER_HH
