//
// Created by FyS on 31/08/17.
//

#include "Authenticator.hh"

fys::gateway::buslistener::Authenticator::~Authenticator() {}

fys::gateway::buslistener::Authenticator::Authenticator(Gateway * const gtw) : _gtw(gtw)
{}

void fys::gateway::buslistener::Authenticator::operator()(const fys::network::Message &message) {
    
}

