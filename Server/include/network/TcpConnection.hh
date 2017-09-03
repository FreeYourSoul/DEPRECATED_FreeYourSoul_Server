//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_TCPCONNECTION_HH
#define FREESOULS_TCPCONNECTION_HH

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <Message.hh>
#include <Context.hh>
#include <FysBus.hh>

namespace fys {
    namespace network {

        class TcpConnection : public std::enable_shared_from_this<TcpConnection>
        {
        public:
            using ptr = std::shared_ptr<TcpConnection>;
            using wptr = std::weak_ptr<TcpConnection>;

            static ptr create(boost::asio::io_service& io_service) {
                return ptr(new TcpConnection(io_service));
            }

            boost::asio::ip::tcp::socket& getSocket();


            void readOnSocket(fys::mq::FysBus<fys::network::Message, gateway::BUS_QUEUES_SIZE>::ptr &fysBus);
            void send(const fys::network::Message& msg);

        private:
            TcpConnection(boost::asio::io_service& io_service);

            void shuttingConnectionDown();

            void handleWrite(const boost::system::error_code &error, size_t bytesTransferred);
            void handleRead(const boost::system::error_code &error, size_t bytesTransferred,
                            fys::mq::FysBus<fys::network::Message, gateway::BUS_QUEUES_SIZE>::ptr &);
        private:
            bool _isShuttingDown;
            boost::asio::ip::tcp::socket _socket;
            unsigned char _buffer[fys::network::MESSAGE_BUFFER_SIZE];
        };

    }
}

#endif //FREESOULS_TCPCONNECTION_HH
