/* 
 * File:   zmqHelper.hpp
 * Author: fys
 *
 * Created on October 14, 2015, 5:58 PM
 */

#ifndef ZMQHELPER_HPP
#define	ZMQHELPER_HPP

#include <zmq.hpp>

namespace zmq 
{

    zmq::message_t     &fillMessage(zmq::message_t &message, const std::string& msg)
    {
        std::memcpy(message.data(), msg.data(), msg.size() + 1); 
        return (message);
    }
    
};

#endif	/* ZMQHELPER_HPP */

