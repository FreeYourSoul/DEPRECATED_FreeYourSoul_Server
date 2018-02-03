//
// Created by FyS on 27/01/18.
//

#include <iostream>
#include "ServerMagicExtractor.hh"

fys::gateway::ServerMagicExtractor::ServerMagicExtractor(const std::string &fullMagic) {
    if (fullMagic.size() < 7)
        std::cout << fullMagic << " is not a magic number" << std::endl;
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

