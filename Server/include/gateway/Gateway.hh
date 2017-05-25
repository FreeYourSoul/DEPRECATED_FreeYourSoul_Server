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

#define GTW_INI_PORT "server.port"
#define GTW_INI_ASIO_THREADS "server.asioThread"
#define GTW_INI_BUS_PATH "bus.iniPath"

namespace fys {
    namespace gateway {

        class Gateway {

        public:
            ~Gateway();
            Gateway();

            void run();

        private:
            void initializeConfiguration(const std::string&);

        private:
            boost::asio::io_service _ios;
            std::map<std::string, fys::network::TcpConnection> _connections;

        };

    }
}

#endif //FREESOULS_GATEWAY_HH
