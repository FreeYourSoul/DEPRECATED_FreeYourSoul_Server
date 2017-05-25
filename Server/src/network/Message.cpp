//
// Created by FyS on 23/05/17.
//

#include <boost/array.hpp>
#include "../../include/network/Message.hh"

fys::network::Message::~Message() {}

fys::network::Message::Message() {
}

fys::network::Message::Message(unsigned char rawMessage[]) {
    std::copy(std::begin(rawMessage), std::end(rawMessage), _rawMessage);
}


unsigned int fys::network::Message::byteToInt(unsigned int index) {
    BitToInt bti;

    for (int i; i < 4; ++i)
        bti.byte[i] = _rawMessage[index + i];
    return bti.integer;
}

unsigned char *fys::network::Message::intToChar(unsigned int toConvert) {
    BitToInt bti;

    bti.integer = toConvert;
    return bti.byte;
}
