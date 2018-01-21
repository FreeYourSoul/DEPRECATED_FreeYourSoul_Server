//
// Created by FyS on 28/08/17.
//

#ifndef FREESOULS_GAMESERVERINSTANCE_HH
#define FREESOULS_GAMESERVERINSTANCE_HH

#include <string>
#include <Range.hpp>

namespace fys::gateway {

    class GameServerInstance {
    public:
        bool operator()(const std::string&) const noexcept;

        void setPort(const ushort port);
        void setIp(const std::string &ip);
        void setPositionId(const std::string &);

        const std::string &getIp() const;
        const std::string &getPositionId() const;
        ushort getPort() const;

    private:
        std::string _positionId;
        std::string _ip;
        ushort _port = 666;
    };

    using AuthServerInstance = GameServerInstance;

}


#endif //FREESOULS_GAMESERVERINSTANCE_HH
