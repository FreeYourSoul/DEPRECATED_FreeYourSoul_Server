//
// Created by FyS on 23/05/17.
//

#include <boost/array.hpp>
#include <cstring>
#include <iostream>
#include <bitset>
#include "../../include/network/Message.hh"

fys::network::Message::~Message() {}

fys::network::Message::Message() : _index(0) {
}

fys::network::Message::Message(unsigned char rawMessage[]) : _index(0) {
    std::copy(rawMessage, rawMessage + fys::network::MESSAGE_BUFFER_SIZE, _rawMessage);
    loadOpCode();
}

void fys::network::Message::loadOpCode() {
    BitConvert btc;

    for (int i = 0; i < 2; ++i)
        btc.byte[i] = _rawMessage[i];
    _opCode = btc.tBytes[0];
    _index = 2;
}

std::string &fys::network::Message::byteToString(std::string &toFill) {
    u_int size = byteToInt();

    toFill.clear();
    if ((_index + size) < MESSAGE_BUFFER_SIZE)
        for (auto i = 0; i < size; ++i)
            toFill += _rawMessage[_index + i];
    _index += size;
    return toFill;
}

u_int fys::network::Message::byteToInt() {
    BitConvert bti;

    if ((_index + 4) < MESSAGE_BUFFER_SIZE)
        for (int i = 0; i < 4; ++i)
            bti.byte[i] = _rawMessage[_index + i];
    _index += 4;
    return bti.integer;
}

const u_char *fys::network::Message::getRawMessage() const {
    return _rawMessage;
}

u_short fys::network::Message::getOpCode() const {
    return _opCode;
}
