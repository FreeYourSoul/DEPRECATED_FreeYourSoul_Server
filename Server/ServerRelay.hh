//
// Created by prout on 11/3/15.
//

#ifndef FREESOULS_SERVERRELAY_HH
#define FREESOULS_SERVERRELAY_HH


#include <zmq.hpp>

class ServerRelay
{

public:
    ~ServerRelay();
    ServerRelay(zmq::context_t &);

    void       work();

private:
    zmq::socket_t   socket;

};


#endif //FREESOULS_SERVERRELAY_HH
