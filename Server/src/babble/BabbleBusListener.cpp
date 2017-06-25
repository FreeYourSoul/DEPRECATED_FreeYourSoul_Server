//
// Created by FyS on 25/05/17.
//

#include <QueueContainer.hh>
#include <Message.hh>
#include "../../include/babble/BabbleBusListener.hh"

fys::gateway::BabbleBusListener::~BabbleBusListener() {}

fys::gateway::BabbleBusListener::BabbleBusListener(fys::mq::FysBus *fysBus) : _fysBus(fysBus) {
    this->setBusRoutingKey(2);
}

void fys::gateway::BabbleBusListener::listen() {
    bool infinite = true;
    while (infinite) {
        fys::mq::QueueContainer<network::Message> *msg =_fysBus->popFromBus(_indexInBus);

    }
}

void fys::gateway::BabbleBusListener::setBusRoutingKey(const u_int indexInBus) {
    this->_indexInBus = indexInBus;
}

