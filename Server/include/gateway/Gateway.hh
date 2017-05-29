//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_GATEWAY_HH
#define FREESOULS_GATEWAY_HH

#include <map>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "FysBus.hh"
#include "TcpConnection.hh"
#include "Context.hh"

namespace fys {
    namespace gateway {

        class Gateway {


        public:
            ~Gateway();
            Gateway(const Context&);

            void run();

        private:
            void initializeConfiguration(const std::string&);

        private:
            boost::asio::io_service _ios;
            boost::asio::ip::tcp::acceptor acceptor_;

            std::map<std::string, fys::network::TcpConnection> _connections;

        };

    }
}

#endif //FREESOULS_GATEWAY_HH
