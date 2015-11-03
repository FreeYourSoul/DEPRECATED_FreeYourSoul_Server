//
// Created by prout on 11/3/15.
//

#include <thread>
#include "ServerProxy.hh"
#include "ServerRelay.hh"

ServerProxy::~ServerProxy() { }

ServerProxy::ServerProxy() : ctx(THREAD_CONTEXT), backend(ctx, ZMQ_DEALER), frontend(ctx, ZMQ_ROUTER)
{
    frontend.bind(FRONTEND_CONNECTION);
    backend.bind(BACKEND_CONNECTION);
}

void                ServerProxy::runProxy()
{
    ServerRelay     relay(ctx);
    std::thread     relayThread(std::bind(&ServerRelay::work, &relay));

    relayThread.detach();
    try
    {
        zmq::proxy(static_cast<void *>(frontend), static_cast<void *>(backend), nullptr);
    }
    catch (std::exception& exception)
    {

    }

}