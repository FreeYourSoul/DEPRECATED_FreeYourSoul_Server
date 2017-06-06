//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_GATEWAY_HH
#define FREESOULS_GATEWAY_HH

#include <map>
#include <boost/asio/ip/tcp.hpp>
#include <SessionManager.hh>
#include "FysBus.hh"
#include "TcpConnection.hh"
#include "Context.hh"

namespace fys {
    namespace gateway {

        class Gateway {

        public:
            ~Gateway();
            Gateway(const Context&, boost::asio::io_service &ios);

            void runPlayerAccept();

        private:
            void handlePlayerConnection(network::TcpConnection::pointer &newSession);

        private:
            boost::asio::io_service &_ios;
            boost::asio::ip::tcp::acceptor _acceptor;

            network::SessionManager _gamerConnections;
            network::SessionManager _serverConnections;
        };

    }
}

#endif //FREESOULS_GATEWAY_HH
