//
// Created by FyS on 30/05/17.
//

#ifndef FREESOULS_CONNECTIONMANAGER_HH
#define FREESOULS_CONNECTIONMANAGER_HH

#include <zconf.h>
#include <vector>

// forward declaration
namespace fys {
    namespace network {
        class TcpConnection;
    }
    namespace pb {
        class FySResponseMessage;
        class FySMessage;
    }
}

namespace fys::network {
    using Token = std::vector<char>;

    class SessionManager {

    public:
        using uptr = std::unique_ptr<SessionManager>;
        using ptr = std::shared_ptr<SessionManager>;
        using wptr = std::weak_ptr<SessionManager>;

        explicit SessionManager(const uint size);

        std::pair<std::string, ushort> getConnectionData(const uint idxInSession) const noexcept;
        void setName(std::string &&name);
        uint addConnection(const std::shared_ptr<TcpConnection>& newConnection);
        void disconnectUser(const uint, const Token &);

        const std::string getConnectionToken(const uint indexInSession) const noexcept;
        void sendResponse(const uint i, pb::FySResponseMessage &&msg) const noexcept;
        void send(const uint i, pb::FySMessage &&msg) const noexcept;

    private:
        inline void connectionHandle(const std::shared_ptr<TcpConnection> &newConnection, const uint i);

    private:
        std::string _name;
        std::vector<std::shared_ptr<TcpConnection> > _connections;
        std::vector<Token> _connectionsToken;
    };

}

#endif //FREESOULS_CONNECTIONMANAGER_HH
