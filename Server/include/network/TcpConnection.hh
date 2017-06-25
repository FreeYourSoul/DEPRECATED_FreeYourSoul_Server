//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_TCPCONNECTION_HH
#define FREESOULS_TCPCONNECTION_HH

#include <boost/enable_shared_from_this.hpp>
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

            static pointer create(boost::asio::io_service& io_service) {
                return pointer(new TcpConnection(io_service));
            }

            boost::asio::ip::tcp::socket& getSocket();


            void readOnSocket();
            void send(const fys::network::Message&);

        private:
            TcpConnection(boost::asio::io_service& io_service);

            void shuttingConnectionDown();

            void handleWrite(const boost::system::error_code &error, size_t bytesTransferred);
            void handleRead(const boost::system::error_code &error, size_t bytesTransferred);

        private:
            bool _isShuttingDown;
            boost::asio::ip::tcp::socket _socket;
            unsigned char _buffer[BUFFER_SIZE];
        };

    }
}

#endif //FREESOULS_TCPCONNECTION_HH
