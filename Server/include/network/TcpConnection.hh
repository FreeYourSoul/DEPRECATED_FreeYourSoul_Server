//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_TCPCONNECTION_HH
#define FREESOULS_TCPCONNECTION_HH


#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/impl/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include "Message.hh"

namespace fys {
    namespace network {

        class TcpConnection : public boost::enable_shared_from_this<TcpConnection>
        {
        public:
            typedef boost::shared_ptr<TcpConnection> pointer;

            static pointer create(boost::asio::io_service& io_service)
            {
                return pointer(new TcpConnection(io_service));
            }

            boost::asio::ip::tcp::socket& socket()
            {
                return _socket;
            }

            void send(const fys::network::Message&)
            {
            }

        private:
            TcpConnection(boost::asio::io_service& io_service)
                    : _socket(io_service)
            {
            }

            void handle_write(const boost::system::error_code& /*error*/,
                              size_t /*bytes_transferred*/)
            { }

            boost::asio::ip::tcp::socket _socket;
        };

    }
}

#endif //FREESOULS_TCPCONNECTION_HH
