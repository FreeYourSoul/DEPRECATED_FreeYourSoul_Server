//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_TCPCONNECTION_HH
#define FREESOULS_TCPCONNECTION_HH

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <Context.hh>

// forward declarations
namespace google::protobuf {
    class Message;
}
namespace fys {
    namespace mq {
        template <typename T, int U>
        class FysBus;
    }

    namespace pb {
        class FySMessage;
    }
}

namespace fys::network {

    /**
     * This class reprensent a connection of a client to the Server
     */
    class TcpConnection : public std::enable_shared_from_this<TcpConnection>
    {
    public:
        using ptr = std::shared_ptr<TcpConnection>;
        using wptr = std::weak_ptr<TcpConnection>;

        static inline ptr create(boost::asio::io_service& io_service) {
            return std::make_shared<TcpConnection>(io_service);
        }

        ~TcpConnection();
        explicit TcpConnection(boost::asio::io_service& io_service);

        boost::asio::ip::tcp::socket& getSocket();
        void readOnSocket(std::shared_ptr<mq::FysBus<pb::FySMessage, gateway::BUS_QUEUES_SIZE> > &fysBus);

        void send(google::protobuf::Message&& msg);
        void setCustomShutdownHandler(const std::function<void()> &customShutdownHandler);

        void setSessionIndex(uint _sessionIndex);
        uint getSessionIndex() const;
        /**
         * \brief Get the remote ip address
         * \return remote port
         */
        std::string getIpAddress() const;
        /**
         * \brief Get the remote port
         * \return remote port
         */
        ushort getPort() const;


    private:

        void shuttingConnectionDown();

        void handleRead(const boost::system::error_code &error, size_t bytesTransferred,
                        std::shared_ptr<mq::FysBus<pb::FySMessage, gateway::BUS_QUEUES_SIZE> >);

    private:
        bool _isShuttingDown;
        uint _sessionIndex;
        boost::asio::ip::tcp::socket _socket;

        static constexpr int MESSAGE_BUFFER_SIZE = 512;
        mutable u_char _buffer[MESSAGE_BUFFER_SIZE];

        std::function<void ()> _customShutdownHandler;
    };
}

#endif //FREESOULS_TCPCONNECTION_HH
