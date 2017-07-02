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

        const u_int FYSP_BABBLE_LOGIN   = 201;
        const u_int FYSP_BABBLE_SEND    = 202;
        const u_int FYSP_BABBLE_WHISPER = 203;
        const u_int FYSP_BABBLE_LOGOUT  = 204;

        class BabbleBusListener : fys::mq::IBusListener<mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr> {

        public:
            ~BabbleBusListener();
            BabbleBusListener(const network::SessionManager *playerSessions);

            void listen(mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr &fysBus);
            void setBusRoutingKey(const u_int);

            void launchListenThread(mq::FysBus<network::Message, 1024>::ptr shared_ptr);

        private:
            Babble _babble;
            u_int _indexInBus;

        };

    }
}


#endif //FREESOULS_BABBLEBUSLISTENER_HH
