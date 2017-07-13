//
// Created by FyS on 06/07/17.
//

#ifndef FREESOULS_FORWARDLISTENER_HH
#define FREESOULS_FORWARDLISTENER_HH

#include <Context.hh>
#include <Message.hh>
#include <FysBus.hh>
#include <IBusListener.hh>

namespace fys {
    namespace gateway {

        class ForwardListener : fys::mq::IBusListener<mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr> {

        public:
            ~ForwardListener();
            ForwardListener();

            void launchListenThread(mq::FysBus<fys::network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr fysBus);
            void listen(mq::FysBus<fys::network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr &fysBus) override;
            void setBusRoutingKey(const u_int indexInBus) override;

        private:
            u_int _indexInBus;

        };

    }
}


#endif //FREESOULS_FORWARDLISTENER_HH
