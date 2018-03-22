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
        GameServerInstance(GameServerInstance &&other) noexcept :
                _positionId(std::move(other._positionId)), _ip(std::move(other._ip)),
                _port(other._port), _indexInServerSession(other._indexInServerSession)
        {}
        GameServerInstance &operator=(GameServerInstance &&other) noexcept {
            if (&other != this) {
                _positionId = std::move(other._positionId);
                _ip = std::move(other._ip);
                _port = other._port;
                _indexInServerSession = other._indexInServerSession;
            }
            return *this;
        }

        bool operator()(const std::string&) const noexcept;

        void setPort(ushort port);
        void setIp(const std::string &ip);
        void setPositionId(const std::string &);
        void setIndexInServerSession(uint);

        const std::string &getIp() const;
        const std::string &getPositionId() const;
        ushort getPort() const;
        uint getIndexInServerSession() const;

    private:
        std::string _positionId;
        std::string _ip;
        ushort _port = 666;
        uint _indexInServerSession;
    };

    using AuthServerInstance = GameServerInstance;

}


#endif //FREESOULS_GAMESERVERINSTANCE_HH
