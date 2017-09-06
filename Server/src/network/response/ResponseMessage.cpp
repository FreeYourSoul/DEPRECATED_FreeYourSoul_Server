//
// Created by FyS on 03/09/17.
//

#include "response/ResponseMessage.hh"

fys::network::ResponseMessage::~ResponseMessage() {}

fys::network::ResponseMessage::ResponseMessage() {}

fys::network::ResponseMessage::ResponseMessage(const fys::network::ResponseMessage &other) :
        _opCode(other._opCode), _token(other._token), _listStrings(other._listStrings), _listIntegers(other._listIntegers)
{}

fys::network::ResponseMessage::ResponseMessage(fys::network::ResponseMessage &&other) :
        _opCode(std::move(other._opCode)), _token(std::move(other._token)),
        _listStrings(std::move(other._listStrings)), _listIntegers(std::move(other._listIntegers))
{}

const fys::network::Message::uptr fys::network::ResponseMessage::generateResponse() {
    return std::make_unique<fys::network::Message>();
}

u_short fys::network::ResponseMessage::get_opCode() const {
    return _opCode;
}

void fys::network::ResponseMessage::set_opCode(u_short _opCode) {
    ResponseMessage::_opCode = _opCode;
}

const std::vector<char> &fys::network::ResponseMessage::get_token() const {
    return _token;
}

void fys::network::ResponseMessage::set_token(const std::vector<char> &_token) {
    ResponseMessage::_token = _token;
}

const std::vector<std::string> &fys::network::ResponseMessage::get_listStrings() const {
    return _listStrings;
}

const std::vector<int> &fys::network::ResponseMessage::get_listIntegers() const {
    return _listIntegers;
}
