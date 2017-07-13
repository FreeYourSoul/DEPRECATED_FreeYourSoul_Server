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

        class BabbleBusListener : fys::mq::IBusListener<mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr> {

        public:
            ~BabbleBusListener();
            BabbleBusListener(const network::SessionManager *playerSessions);

            void listen(mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr &fysBus) override;
            void setBusRoutingKey(const u_int) override;

            void launchListenThread(mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr shared_ptr);

        private:
            Babble _babble;
            u_int _indexInBus;

        };

    }
}


#endif //FREESOULS_BABBLEBUSLISTENER_HH
