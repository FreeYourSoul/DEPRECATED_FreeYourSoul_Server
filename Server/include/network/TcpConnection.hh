//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_TCPCONNECTION_HH
#define FREESOULS_TCPCONNECTION_HH

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <Context.hh>
#include <FysBus.hh>
#include <FySGtwMessage.pb.h>

namespace fys {
    namespace network {

        static const int MESSAGE_BUFFER_SIZE = 100;

        class TcpConnection : public std::enable_shared_from_this<TcpConnection>
        {
        public:
            using ptr = std::shared_ptr<TcpConnection>;
            using wptr = std::weak_ptr<TcpConnection>;

            static ptr create(boost::asio::io_service& io_service) {
                return std::make_shared<TcpConnection>(io_service);
            }

            TcpConnection(boost::asio::io_service& io_service);

            boost::asio::ip::tcp::socket& getSocket();

            void setCustomShutdownHandler(const std::function<void()> &customShutdownHandler);

            void readOnSocket(fys::mq::FysBus<fys::pb::FySGtwMessage, gateway::BUS_QUEUES_SIZE>::ptr &fysBus);
            void send(const fys::pb::FySGtwMessage& msg);

            uint getSessionIndex() const;
            void setSessionIndex(uint _sessionIndex);


        private:

            void shuttingConnectionDown();

            void handleWrite(const boost::system::error_code &error, const size_t bytesTransferred);
            void handleRead(const boost::system::error_code &error, const size_t bytesTransferred,
                            fys::mq::FysBus<fys::pb::FySGtwMessage, gateway::BUS_QUEUES_SIZE>::ptr);

        private:
            bool _isShuttingDown;
            uint _sessionIndex;
            boost::asio::ip::tcp::socket _socket;

            unsigned char _buffer[fys::network::MESSAGE_BUFFER_SIZE];

            std::function<void ()> _customShutdownHandler;
        };

    }
}

#endif //FREESOULS_TCPCONNECTION_HH
