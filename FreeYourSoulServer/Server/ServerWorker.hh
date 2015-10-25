/* 
 * File:   ServerWorker.hpp
 * Author: fys
 *
 * Created on October 5, 2015, 8:54 PM
 */

#ifndef SERVERWORKER_HPP
#define	SERVERWORKER_HPP

#include <zmq.hpp>

#include "ActionDispatcher.hh"
#include "Authenticator.hh"

class ServerWorker 
{
public:
    ~ServerWorker();
    ServerWorker(zmq::context_t &ctx);
    
    void work();

private:
    zmq::context_t      &ctx;
    zmq::socket_t       socket;
    Authenticator       auth;
    ActionDispatcher    dispatcher;
    
};

#endif	/* SERVERWORKER_HPP */
