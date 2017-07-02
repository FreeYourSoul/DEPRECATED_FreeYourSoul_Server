//
// Created by FyS on 25/05/17.
//

#include <QueueContainer.hh>
#include <Message.hh>
#include <thread>
#include <boost/thread.hpp>
#include "../../include/babble/BabbleBusListener.hh"

fys::gateway::BabbleBusListener::~BabbleBusListener() {}

fys::gateway::BabbleBusListener::BabbleBusListener(const network::SessionManager *playerSessions) : _babble(playerSessions) {
    this->setBusRoutingKey(2);
}

void fys::gateway::BabbleBusListener::listen(fys::mq::FysBus<network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr &fysBus) {
    bool infinite = true;
    std::cout << "Babble listener launched : " << _indexInBus << std::endl;
    while (infinite) {
        fys::mq::QueueContainer<network::Message> *msgContainer = fysBus->popFromBus(_indexInBus);
        if (msgContainer != NULL) {
            switch (msgContainer->getOpCodeMsg()) {
                case FYSP_BABBLE_SEND:
                    _babble.sendMessage(msgContainer->getContained());
                break;
                case FYSP_BABBLE_WHISPER:
                    _babble.whisperMessage(msgContainer->getContained());
                break;
                case FYSP_BABBLE_LOGIN:
                    _babble.signInOnBabble(msgContainer->get_tokenUser());
                break;
                case FYSP_BABBLE_LOGOUT:
                    _babble.signOutFromBabble(msgContainer->get_tokenUser());
                break;
                default:
                    // TODO error management
                    break;
            }
        }
    }
}

void fys::gateway::BabbleBusListener::setBusRoutingKey(const u_int indexInBus) {
    this->_indexInBus = indexInBus;
}

void fys::gateway::BabbleBusListener::launchListenThread(fys::mq::FysBus<fys::network::Message, 1024>::ptr fysBus) {
    boost::thread babbleListenerThread(boost::bind(&BabbleBusListener::listen, this, fysBus));
    babbleListenerThread.detach();
}

