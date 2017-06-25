//
// Created by FyS on 25/05/17.
//

#ifndef FREESOULS_BABBLEBUSLISTENER_HH
#define FREESOULS_BABBLEBUSLISTENER_HH


#include <IBusListener.hh>
#include <FysBus.hh>
#include <Gateway.hh>
#include <Babble.hh>

namespace fys {
    namespace gateway {

        class BabbleBusListener : fys::mq::IBusListener {

        public:
            ~BabbleBusListener();
            BabbleBusListener(mq::FysBus *);

            void listen();
            void setBusRoutingKey(const u_int);

        private:
            mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE> *_fysBus;
            Babble _babble;
            u_int _indexInBus;

        };

    }
}


#endif //FREESOULS_BABBLEBUSLISTENER_HH
