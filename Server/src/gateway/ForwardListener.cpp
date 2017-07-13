//
// Created by FyS on 06/07/17.
//

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "ForwardListener.hh"

fys::gateway::ForwardListener::~ForwardListener() {}

fys::gateway::ForwardListener::ForwardListener() {}

void fys::gateway::ForwardListener::launchListenThread(fys::mq::FysBus<fys::network::Message, GATEWAY_BUS_QUEUES_SIZE
>::ptr fysBus) {
    boost::thread babbleListenerThread(boost::bind(&ForwardListener::listen, this, fysBus));
    babbleListenerThread.detach();
}

void fys::gateway::ForwardListener::listen(fys::mq::FysBus<fys::network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr &fysBus) {
    std::cout << "listener launched : " << _indexInBus << std::endl;
    while (true) {
        fys::mq::QueueContainer<network::Message> *msgContainer = fysBus-> popFromBus(_indexInBus);

    }
}

void fys::gateway::ForwardListener::setBusRoutingKey(const u_int indexInBus) {
    this ->_indexInBus = indexInBus;
}


