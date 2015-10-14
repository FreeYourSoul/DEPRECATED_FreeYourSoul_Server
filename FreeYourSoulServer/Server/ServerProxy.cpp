/* 
 * File:   ServerProxy.cpp
 * Author: fys
 * 
 * Created on October 5, 2015, 8:53 PM
 */

#include <thread>

#include "ServerProxy.hpp"

ServerProxy::~ServerProxy()
{
}

ServerProxy::ServerProxy() :
  ctx(THREAD_CONTEXT),
  backend(ctx, ZMQ_DEALER),
  frontend(ctx, ZMQ_ROUTER),
  worker(ctx)
{
  frontend.bind(std::string("tcp://*:") + PORT_SERVER);
  backend.bind(INPROC_SERVER);
}

void ServerProxy::run()
{
  std::thread worker_thread(&ServerWorker::work, &worker);
  worker_thread.detach();
}
