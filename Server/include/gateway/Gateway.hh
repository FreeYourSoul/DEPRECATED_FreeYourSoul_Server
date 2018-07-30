//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_GATEWAY_HH
#define FREESOULS_GATEWAY_HH

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <SessionManager.hh>
#include <Context.hh>

// forward declarations
namespace fys {
    namespace mq {
        template<typename T, int U>
        class FysBus;
    }
    namespace pb {
        class FySMessage;
    }
}

namespace fys::gateway {

        class Gateway {
        public:
            using uptr = std::unique_ptr<Gateway>;
            using ptr = std::shared_ptr<Gateway>;
            using wptr = std::weak_ptr<Gateway>;

        public:
            Gateway(const Context &ctx, boost::asio::io_service &ios,
                    std::shared_ptr<mq::FysBus<pb::FySMessage, BUS_QUEUES_SIZE>> fysBus);

            static void start(const Context &ctx);

            static inline
            ptr create(const Context &ctx, boost::asio::io_service &ios,
                       std::shared_ptr<fys::mq::FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>> &fysBus) {
                return std::make_shared<Gateway>(ctx, ios, fysBus);
            }

            void runPlayerAccept();
            void runServerAccept();

            void addGameServer(uint, const std::string &, const std::string &string);
            void setAuthServer(uint);
            const GameServerInstance &getServerForAuthenticatedUser(const std::string&);

            bool isAuthServerSet() const {
                //     return _authServer.getPort() > 0 && !_authServer.getIp().empty();
                return true;
            }

            bool isGameServerInstancesHasPositionId(const std::string& positionId) const;

            network::SessionManager &getGamerConnections() { return _gamerConnections; }
            network::SessionManager &getServerConnections() { return _serverConnections; }

        private:
            boost::asio::io_service &_ios;
            boost::asio::ip::tcp::acceptor _acceptorPlayer;
            boost::asio::ip::tcp::acceptor _acceptorServer;
            std::shared_ptr<fys::mq::FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>>_fysBus;

            network::SessionManager _gamerConnections;
            network::SessionManager _serverConnections;
            std::vector<GameServerInstance> _gameServers;
            AuthServerInstance _authServer;
        };

}

#endif //FREESOULS_GATEWAY_HH
