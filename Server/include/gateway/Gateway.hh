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

namespace fys {
    namespace gateway {

        class Gateway {

        public:
            ~Gateway();
            Gateway(const Context &ctx, boost::asio::io_service &ios, fys::mq::FysBus<fys::network::Message, BUS_QUEUES_SIZE>::ptr &fysBus);

            void runPlayerAccept();
            const network::SessionManager *getGamerConnectionsPointer() const;

        private:
            void handlePlayerConnection(network::TcpConnection::ptr &newSession);

        private:
            boost::asio::io_service &_ios;
            boost::asio::ip::tcp::acceptor _acceptor;
            fys::mq::FysBus<fys::network::Message, BUS_QUEUES_SIZE>::ptr _fysBus;

            network::SessionManager _gamerConnections;
            network::SessionManager _serverConnections;
        };

    }
}

#endif //FREESOULS_GATEWAY_HH
