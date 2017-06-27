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

        const u_int FYSP_BABBLE_LOGIN   = 401;
        const u_int FYSP_BABBLE_SEND    = 402;
        const u_int FYSP_BABBLE_WHISPER = 403;
        const u_int FYSP_BABBLE_LOGOUT  = 404;

        class BabbleBusListener : fys::mq::IBusListener<mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE>> {

        public:
            ~BabbleBusListener();
            BabbleBusListener();

            void listen(mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE> *fysBus);
            void setBusRoutingKey(const u_int);

        private:

            Babble _babble;
            u_int _indexInBus;

        };

    }
}


#endif //FREESOULS_BABBLEBUSLISTENER_HH
