//
// Created by FyS on 28/08/17.
//

#ifndef FREESOULS_GAMESERVERINSTANCE_HH
#define FREESOULS_GAMESERVERINSTANCE_HH

#include <string>

namespace fys {
    namespace gateway {

        class GameServerInstance {
        public:
            ~GameServerInstance();
            GameServerInstance();

            const std::string &getIp() const;

            void setIp(const std::string &ip);

            const std::string &getPort() const;

            void setPort(const std::string &port);

        private:
            std::string _ip;
            std::string _port;
        };

    }
}


#endif //FREESOULS_GAMESERVERINSTANCE_HH
