//
// Created by FyS on 27/01/18.
//

#include <iostream>
#include <spdlog/spdlog.h>
#include "ServerMagicExtractor.hh"

fys::gateway::ServerMagicExtractor::ServerMagicExtractor(const std::string &fullMagic) {
    if (fullMagic.size() < 7)
        spdlog::get("c")->warn("{} is not a magic number", fullMagic);
    else {
        _magic = fullMagic.substr(0, fullMagic.size() - 7);
        _positionId = fullMagic.substr(fullMagic.size() - 7);
    }
}

const std::string &fys::gateway::ServerMagicExtractor::getMagic() const {
    return _magic;
}

const std::string &fys::gateway::ServerMagicExtractor::getPositionId() const {
    return _positionId;
}

