//
// Created by prout on 11/3/15.
//

#ifndef FREESOULS_SERVERPROXY_HH
#define FREESOULS_SERVERPROXY_HH

#include <zmq.hpp>

#define THREAD_CONTEXT          1
#define FRONTEND_CONNECTION     "tcp://*:1337"
#define BACKEND_CONNECTION      "inproc://backend"

class ServerProxy
{
public:
    ~ServerProxy();
    ServerProxy();

    void            runProxy();

private:
    zmq::context_t  ctx;
    zmq::socket_t   backend;
    zmq::socket_t   frontend;

};


#endif //FREESOULS_SERVERPROXY_HH
