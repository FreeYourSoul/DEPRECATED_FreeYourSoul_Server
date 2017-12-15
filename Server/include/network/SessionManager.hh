//
// Created by FyS on 30/05/17.
//

#ifndef FREESOULS_CONNECTIONMANAGER_HH
#define FREESOULS_CONNECTIONMANAGER_HH

#include <zconf.h>
#include <list>
#include <FySMessage.pb.h>
#include "TcpConnection.hh"

namespace fys::network {
    using Token = std::vector<char>;

    class SessionManager {

    public:
        using uptr = std::unique_ptr<SessionManager>;
        using ptr = std::shared_ptr<SessionManager>;
        using wptr = std::weak_ptr<SessionManager>;

        explicit SessionManager(const u_int size);

        std::string getConnectionToken(const uint indexInSession) const noexcept;
        std::pair<std::string, ushort> getConnectionData(const uint indexInSession) const noexcept;
        const u_int addConnection(const TcpConnection::ptr& newConnection);
        void disconnectUser(const Token &);

        void sendResponse(uint i, pb::FySResponseMessage &&message) const noexcept;

    private:
        inline void connectionHandle(const fys::network::TcpConnection::ptr &newConnection, const uint i);

    private:
        std::vector<fys::network::TcpConnection::ptr> _connections;
        std::vector<Token > _connectionsToken;
    };

}


#endif //FREESOULS_CONNECTIONMANAGER_HH
