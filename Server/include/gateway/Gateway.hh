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
#include <FySGtwMessage.pb.h>

namespace fys {
    namespace gateway {

        class Gateway {

        public:
            using uptr = std::unique_ptr<Gateway>;
            using ptr = std::shared_ptr<Gateway>;
            using wptr = std::weak_ptr<Gateway>;

        public:
            ~Gateway();
            Gateway(const Context &ctx, boost::asio::io_service &ios, fys::mq::FysBus<fys::pb::FySGtwMessage, BUS_QUEUES_SIZE>::ptr &fysBus);

            static inline ptr create(const Context &ctx, boost::asio::io_service &ios, fys::mq::FysBus<fys::pb::FySGtwMessage, BUS_QUEUES_SIZE>::ptr &fysBus) {
                return std::make_shared<Gateway>(ctx, ios, fysBus);
            }

            void runPlayerAccept();
            void runServerAccept();

            void addGameServer(const uint);
            void setAuthServer(const uint);

            bool isAuthServerSet() const;

            const network::SessionManager &getGamerConnections() const;
            const network::SessionManager &getServerConnections() const;

        private:
            boost::asio::io_service &_ios;
            boost::asio::ip::tcp::acceptor _acceptorPlayer;
            boost::asio::ip::tcp::acceptor _acceptorServer;
            fys::mq::FysBus<fys::pb::FySGtwMessage, BUS_QUEUES_SIZE>::ptr _fysBus;

            network::SessionManager _gamerConnections;
            network::SessionManager _serverConnections;
            std::vector<GameServerInstance> _gameServers;
            AuthServerInstance _authServer;
        };

    }
}

#endif //FREESOULS_GATEWAY_HH
