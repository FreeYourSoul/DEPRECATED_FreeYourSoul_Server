//
// Created by FyS on 25/05/17.
//

#include <QueueContainer.hh>
#include <thread>
#include <boost/thread.hpp>
#include "BabbleMessage.hh"
#include "BabbleBusListener.hh"

fys::gateway::BabbleBusListener::~BabbleBusListener() {}

fys::gateway::BabbleBusListener::BabbleBusListener(const network::SessionManager *playerSessions) : _babble(playerSessions) {
    this->setBusRoutingKey(2);
}

void fys::gateway::BabbleBusListener::launchListenThread(fys::mq::FysBus<fys::network::Message, GATEWAY_BUS_QUEUES_SIZE
>::ptr fysBus) {
    boost::thread babbleListenerThread(boost::bind(&BabbleBusListener::listen, this, fysBus));
    babbleListenerThread.detach();
}

void fys::gateway::BabbleBusListener::listen(fys::mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr &fysBus) {
    std::cout << "Babble listener launched : " << _indexInBus << std::endl;
    while (true) {
        fys::mq::QueueContainer<network::Message> *msgContainer = fysBus->popFromBus(_indexInBus);

        if (msgContainer != NULL) {
            fys::network::BabbleMessage babbleMessage;
            fys::gateway::Babble::funcPtr func;

            func = babbleMessage.initialize(msgContainer->getContained());
            if (func != nullptr)
                (_babble.*func)(babbleMessage);
            else
            {}; // TODO Manage error
        }
    }
}

void fys::gateway::BabbleBusListener::setBusRoutingKey(const u_int indexInBus) {
    this->_indexInBus = indexInBus;
}

