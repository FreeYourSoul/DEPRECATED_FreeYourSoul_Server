/* 
 * File:   ServerWorker.cpp
 * Author: fys
 * 
 * Created on October 5, 2015, 8:54 PM
 */

#include "ServerWorker.hh"
#include "ServerProxy.hh"

ServerWorker::~ServerWorker()
{
}

ServerWorker::ServerWorker(zmq::context_t &ctx) :
 ctx(ctx),
 socket(ctx, ZMQ_DEALER)
{
  socket.connect(INPROC_SERVER);
}

void ServerWorker::work() 
{
  
}

