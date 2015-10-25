/* 
 * File:   ServerProxy.cpp
 * Author: fys
 * 
 * Created on October 5, 2015, 8:53 PM
 */

#include <thread>
#include <iostream>

#include "ServerProxy.hh"
#include "Logs/Logs.hpp"

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
  Logs::getInstance(ctx)->writeLog(Logs::INFO, "Server started");
  std::thread worker_thread(&ServerWorker::work, &worker);
  worker_thread.detach();
  try {
      Logs::getInstance()->writeLog(Logs::INFO, "Server Worker proxy launched");
      zmq::proxy(static_cast<void *> (frontend), static_cast<void *> (backend), NULL);
  }   
  catch (std::exception &e) {
      Logs::getInstance()->writeLog(Logs::ERROR, "Server Worker proxy failed " + std::string(e.what()));
  }
}
