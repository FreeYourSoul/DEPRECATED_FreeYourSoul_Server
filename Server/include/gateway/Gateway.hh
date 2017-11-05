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

            void runPlayerAccept();
            void runServerAccept();

            const network::SessionManager *getGamerConnectionsPointer() const;
            const network::SessionManager *getServerConnectionsPointer() const;

        private:
            void handlePlayerConnection(network::TcpConnection::ptr &newSession);
            void handleServerConnection(network::TcpConnection::ptr &newSession);

        private:
            boost::asio::io_service &_ios;
            boost::asio::ip::tcp::acceptor _acceptorPlayer;
            boost::asio::ip::tcp::acceptor _acceptorServer;
            fys::mq::FysBus<fys::pb::FySGtwMessage, BUS_QUEUES_SIZE>::ptr _fysBus;

            network::SessionManager _gamerConnections;
            network::SessionManager _serverConnections;
        };

    }
}

#endif //FREESOULS_GATEWAY_HH
