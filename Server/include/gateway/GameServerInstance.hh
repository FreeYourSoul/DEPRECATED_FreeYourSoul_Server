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
        ~GameServerInstance() = default;
        GameServerInstance() : GameServerInstance(0, 0, 0, 0) {}
        GameServerInstance(uint minX, uint maxX, uint minY, uint maxY) :
                _range(minX, maxX, minY, maxY), _ip() {}
        GameServerInstance(const GameServerInstance&) = default;
        GameServerInstance(GameServerInstance&&) noexcept;
        GameServerInstance &operator=(GameServerInstance &&) noexcept;

        bool operator()(const uint xPos, const uint yPos) const noexcept;

        void setPort(const ushort port);
        void setIp(const std::string &ip);

        const std::string &getIp() const;
        ushort getPort() const;

    private:
        utils::Range<> _range;
        std::string _ip;
        ushort _port = 666;
    };

    using AuthServerInstance = GameServerInstance;

}


#endif //FREESOULS_GAMESERVERINSTANCE_HH
