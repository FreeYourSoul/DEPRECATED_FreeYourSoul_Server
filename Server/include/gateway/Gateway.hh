//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_GATEWAY_HH
#define FREESOULS_GATEWAY_HH

#include <map>
#include <boost/asio/ip/tcp.hpp>
#include <SessionManager.hh>
#include <FysBus.hh>
#include <TcpConnection.hh>
#include <Context.hh>
#include <FySMessage.pb.h>

namespace fys::gateway {

        class Gateway {
        public:
            using uptr = std::unique_ptr<Gateway>;
            using ptr = std::shared_ptr<Gateway>;
            using wptr = std::weak_ptr<Gateway>;

        public:
            Gateway(const Context &ctx, boost::asio::io_service &ios, fys::mq::FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>::ptr &fysBus);

            static void start(const Context &ctx);

            static inline ptr create(const Context &ctx, boost::asio::io_service &ios, fys::mq::FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>::ptr &fysBus) {
                return std::make_shared<Gateway>(ctx, ios, fysBus);
            }

            void runPlayerAccept();
            void runServerAccept();

            void addGameServer(uint, const std::string &string);
            void setAuthServer(const uint);
            const GameServerInstance &getServerForAuthenticatedUser(const std::string&);

            bool isAuthServerSet() const {
                //     return _authServer.getPort() > 0 && !_authServer.getIp().empty();
                return true;
            }

            bool isGameServerInstancesHasPositionId(const std::string& positionId) const;

            const network::SessionManager &getGamerConnections() const { return _gamerConnections; }
            const network::SessionManager &getServerConnections() const { return _serverConnections; }

            void setGamerConnections(const network::SessionManager &_gamerConnections) {}
            void setGerverConnections(const network::SessionManager &_serverConnections) {}

        private:
            boost::asio::io_service &_ios;
            boost::asio::ip::tcp::acceptor _acceptorPlayer;
            boost::asio::ip::tcp::acceptor _acceptorServer;
            fys::mq::FysBus<fys::pb::FySMessage, BUS_QUEUES_SIZE>::ptr _fysBus;

            network::SessionManager _gamerConnections;
            network::SessionManager _serverConnections;
            std::vector<GameServerInstance> _gameServers;
            AuthServerInstance _authServer;
        };

}

#endif //FREESOULS_GATEWAY_HH
