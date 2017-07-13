//
// Created by FyS on 23/05/17.
//

#include <boost/array.hpp>
#include <cstring>
#include <iostream>
#include <bitset>
#include "../../include/network/Message.hh"

fys::network::Message::~Message() {}
fys::network::Message::Message() {
}

fys::network::Message::Message(unsigned char rawMessage[]) {
    std::copy(rawMessage, rawMessage + fys::network::BUFFER_SIZE, _rawMessage);
    loadOpCode();
}

void fys::network::Message::loadOpCode() {
    BitConvert btc;

    for (int i = 0; i < 2; ++i)
        btc.byte[i] = _rawMessage[i];
    _opCode = btc.tBytes[0];
}

std::string &fys::network::Message::byteToString(std::string &toFill, const unsigned int size, const unsigned int index) const {
    toFill.clear();
    if ((index + size) >= BUFFER_SIZE)
        for (int i = 0; i < size; ++i)
            toFill += _rawMessage[index + i];
    return toFill;
}

unsigned int fys::network::Message::byteToInt(const unsigned int index) const {
    BitConvert bti;

    if ((index + 4) >= BUFFER_SIZE)
        for (int i = 0; i < 4; ++i)
            bti.byte[i] = _rawMessage[index + i];
    return bti.integer;
}

const unsigned char *fys::network::Message::getRawMessage() const {
    return _rawMessage;
}

unsigned short fys::network::Message::getOpCode() const {
    return _opCode;
}
