//
// Created by FyS on 25/05/17.
//

#ifndef FREESOULS_BABBLEBUSLISTENER_HH
#define FREESOULS_BABBLEBUSLISTENER_HH


#include <IBusListener.hh>

namespace fys {
    namespace gateway {

        class BabbleBusListener : fys::mq::IBusListener {

        public:
            ~BabbleBusListener();
            BabbleBusListener();

            void listen();
            void setBusRoutingKey(const u_int);

        private:
            u_int routingKey;

        };

    }
}


#endif //FREESOULS_BABBLEBUSLISTENER_HH
