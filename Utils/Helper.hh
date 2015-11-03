//
// Created by prout on 11/3/15.
//

#ifndef FREESOULS_HELPER_HH
#define FREESOULS_HELPER_HH


#include <zmq.hpp>

namespace zmq
{
    class Helper
    {

    public:
        template <class Type>
        static zmq::message_t     &fillMessage(zmq::message_t &message, const Type *msg)
        {
            std::memcpy(message.data(), msg, sizeof(Type));
            return (message);
        }

        static zmq::message_t     &fillMessage(zmq::message_t &message, const std::string& msg)
        {
            std::memcpy(message.data(), msg.data(), msg.size() + 1);
            return (message);
        }
    };
}

#endif //FREESOULS_HELPER_HH
