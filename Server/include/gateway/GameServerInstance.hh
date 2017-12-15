//
// Created by FyS on 28/08/17.
//

#ifndef FREESOULS_GAMESERVERINSTANCE_HH
#define FREESOULS_GAMESERVERINSTANCE_HH

#include <string>

namespace fys::gateway {

    class GameServerInstance {
    public:
        ~GameServerInstance() = default;
        GameServerInstance() = default;
        GameServerInstance(const GameServerInstance&) = default;
        GameServerInstance(GameServerInstance&&) noexcept;
        GameServerInstance &operator=(GameServerInstance &&) noexcept;

        void setPort(const ushort port);
        void setIp(const std::string &ip);

        const std::string &getIp() const;
        ushort getPort() const;

    private:
        std::string _ip;
        ushort _port = 666;
    };

    using AuthServerInstance = GameServerInstance;

}


#endif //FREESOULS_GAMESERVERINSTANCE_HH
