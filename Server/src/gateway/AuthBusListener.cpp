//
// Created by FyS on 25/05/17.
//

#include "AuthBusListener.hh"

fys::gateway::AuthBusListener::~AuthBusListener() {}

fys::gateway::AuthBusListener::AuthBusListener() {}

void fys::gateway::AuthBusListener::listen() {

}

void fys::gateway::AuthBusListener::setBusRoutingKey(const u_int indexInBus) {
    this->_indexInBus = indexInBus;
}
