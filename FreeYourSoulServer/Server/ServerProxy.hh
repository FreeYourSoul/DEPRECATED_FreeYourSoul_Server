/* 
 * File:   ServerProxy.h
 * Author: fys
 *
 * Created on October 5, 2015, 8:53 PM
 */

#ifndef SERVERPROXY_HPP
#define	SERVERPROXY_HPP

#include <zmq.hpp>

#include "ServerWorker.hh"

#define THREAD_CONTEXT 1
#define PORT_SERVER "5555"
#define INPROC_SERVER "inproc://backend_server"

class ServerProxy {
public:
    ~ServerProxy();
    ServerProxy();
    
    void run();

private:
    zmq::context_t ctx;
    zmq::socket_t backend;
    zmq::socket_t frontend;
    ServerWorker worker;
};

#endif	/* SERVERPROXY_HPP */

