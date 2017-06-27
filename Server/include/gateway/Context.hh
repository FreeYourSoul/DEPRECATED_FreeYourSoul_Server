//
// Created by FyS on 26/05/17.
//

#ifndef FREESOULS_CONTEXT_HH
#define FREESOULS_CONTEXT_HH

#include <string>
#include <ostream>

#define GTW_INI_PORT "server.port"
#define GTW_INI_ASIO_THREADS "server.asioThread"
#define GTW_INI_BUS_PATH "bus.iniPath"
#define GTW_QUEUES_SIZE "bus.queuesSize"

#define  GATEWAY_BUS_QUEUES_SIZE 1024

namespace fys {
    namespace gateway {

        class Context {

        public:
            ~Context();
            Context(const int ac, const char *const *av);

            friend std::ostream &operator<<(std::ostream &os, const Context &context);

            std::size_t getPort() const;
            void setPort(const std::size_t port);
            const std::string &getBusIniFilePath() const;
            void setBusIniFilePath(const std::string &busIniFilePath);
            size_t getAsioThread() const;
            void setAsioThread(const size_t asioThread);
            std::size_t getQueuesSize() const;
            bool isVerbose() const;
            void setVerbose(bool _verbose);
            void setQueuesSize(const std::size_t _queuesSize);

        private:
            void initializeFromIni(const std::string &iniPath);

        private:
            std::size_t _port;
            std::size_t _asioThread;
            std::string _busIniFilePath;
            std::size_t _queuesSize;
            bool _verbose;
        };

    }
}


#endif //FREESOULS_CONTEXT_HH
