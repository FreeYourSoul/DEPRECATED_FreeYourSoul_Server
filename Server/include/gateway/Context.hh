//
// Created by FyS on 26/05/17.
//

#ifndef FREESOULS_CONTEXT_HH
#define FREESOULS_CONTEXT_HH

#include <string>

#define GTW_INI_PORT "server.port"
#define GTW_INI_ASIO_THREADS "server.asioThread"
#define GTW_INI_BUS_PATH "bus.iniPath"

namespace fys {
    namespace gateway {

        class Context {

        public:
            ~Context();
            Context(const std::string& iniPath);

            short getPort() const;

            void setPort(const short port);

            const std::string &getBusIniFilePath() const;

            void setBusIniFilePath(const std::string &busIniFilePath);

            size_t getAsioThread() const;

            void setAsioThread(const size_t asioThread);

        private:
            short port;
            std::size_t asioThread;
            std::string busIniFilePath;

        };

    }
}


#endif //FREESOULS_CONTEXT_HH
