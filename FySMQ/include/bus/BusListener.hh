//
// Created by FyS on 29/08/17.
//

#ifndef FREESOULS_BUSLISTENER_HH
#define FREESOULS_BUSLISTENER_HH

#include <zconf.h>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <QueueContainer.hh>

namespace fys {
    namespace mq {

/**
 * MsgType : Message type gotten from the queue listenned in the Bus
 * Functor : Functor to execute for the message listenned
 *
 */
        template <typename Functor, typename BusType>
        class BusListener {

        public:
            ~BusListener() {}
            explicit BusListener(const u_int indexInBus, Functor func) : _indexInBus(indexInBus), _functor(func) {
            }

            void launchListenThread(typename BusType::ptr bus, const bool launchTread = true) {
                if (launchTread) {
                    boost::thread babbleListenerThread(boost::bind(&BusListener::listen, this, bus));
                    babbleListenerThread.detach();
                }
                else
                    listen(bus);
            }

        private:
            void listen(typename BusType::ptr bus) {
                if (!bus->isIndexQueueLegitimate(_indexInBus)) {
                    std::cerr << "Listener couldn't be launched; the index in bus is not legitimate" << std::endl;
                    return;
                }
                std::cout << "Listener launched, listen on queue :" << _indexInBus << std::endl;
                while (true) {
                    auto *msgContainer = bus->popFromBus(_indexInBus);
                    if (msgContainer)
                        _functor(msgContainer);
                }
            }

        private:
            u_int _indexInBus;
            Functor _functor;

        };

    }
}

#endif //FREESOULS_BUSLISTENER_HH
