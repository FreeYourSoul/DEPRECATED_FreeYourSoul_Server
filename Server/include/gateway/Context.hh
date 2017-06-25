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

namespace fys {
    namespace gateway {

        class Context {

        public:
            ~Context();
            Context();
            Context(const std::string& iniPath);

            std::ostream &operator<<(std::ostream &os);

            std::size_t getPort() const;
            void setPort(const std::size_t port);
            const std::string &getBusIniFilePath() const;
            void setBusIniFilePath(const std::string &busIniFilePath);
            size_t getAsioThread() const;
            void setAsioThread(const size_t asioThread);

            std::size_t getQueuesSize() const;

            void setQueuesSize(const std::size_t _queuesSize);

        private:
            void initializeFromIni(const std::string &iniPath);

        private:
            std::size_t _port;
            std::size_t _asioThread;
            std::string _busIniFilePath;
            std::size_t _queuesSize;
        };

    }
}


#endif //FREESOULS_CONTEXT_HH
