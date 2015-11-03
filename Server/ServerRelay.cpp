//
// Created by prout on 11/3/15.
//

#include "ServerRelay.hh"
#include "ServerProxy.hh"

ServerRelay::~ServerRelay() { }

ServerRelay::ServerRelay(zmq::context_t &ctx) : socket(ctx, ZMQ_DEALER)
{
    socket.connect(BACKEND_CONNECTION);
}

void        ServerRelay::work()
{
    while (true)
    {

    }
}