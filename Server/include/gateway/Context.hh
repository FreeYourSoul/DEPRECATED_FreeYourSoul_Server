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

namespace fys {
    namespace gateway {

        class Context {

        public:
            ~Context();
            Context();
            Context(const std::string& iniPath);

            std::ostream &operator<<(std::ostream &os);

            unsigned short getPort() const;
            void setPort(const unsigned short port);
            const std::string &getBusIniFilePath() const;
            void setBusIniFilePath(const std::string &busIniFilePath);
            size_t getAsioThread() const;
            void setAsioThread(const size_t asioThread);

        private:
            void initializeFromIni(const std::string &iniPath);

        private:
            unsigned short _port;
            std::size_t _asioThread;
            std::string _busIniFilePath;

        };

    }
}


#endif //FREESOULS_CONTEXT_HH
