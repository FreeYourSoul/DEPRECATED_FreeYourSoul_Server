//
// Created by FyS on 25/05/17.
//

#include <QueueContainer.hh>
#include <Message.hh>
#include "../../include/babble/BabbleBusListener.hh"

fys::gateway::BabbleBusListener::~BabbleBusListener() {}

fys::gateway::BabbleBusListener::BabbleBusListener() {
    this->setBusRoutingKey(2);
}

void fys::gateway::BabbleBusListener::listen(fys::mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE> *fysBus) {
    bool infinite = true;
    while (infinite) {
        fys::mq::QueueContainer<network::Message> *msg =fysBus->popFromBus(_indexInBus);
        switch (msg->getRoutingKey()) {
            case FYSP_BABBLE_SEND:
                _babble.sendMessage(msg->getContained());
                break;
            case FYSP_BABBLE_WHISPER:
                _babble.whisperMessage(msg->getContained());
                break;
            case FYSP_BABBLE_LOGIN:
                _babble.signInOnBabble(msg->get_tokenUser());
                break;
            case FYSP_BABBLE_LOGOUT:
                _babble.signOutFromBabble(msg->get_tokenUser());
                break;
            default:
                // TODO error management
                break;
        }
    }
}

void fys::gateway::BabbleBusListener::setBusRoutingKey(const u_int indexInBus) {
    this->_indexInBus = indexInBus;
}

