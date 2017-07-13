//
// Created by FyS on 06/07/17.
//

#ifndef FREESOULS_AUTHMESSAGE_HH
#define FREESOULS_AUTHMESSAGE_HH

#include <string>

namespace fys {
    namespace network {

        class AuthMessage {
        public:
            ~AuthMessage();
            AuthMessage();

        private:
            std::string _user;
            std::string _password;
            std::string _token;
        };

    }
}


#endif //FREESOULS_AUTHMESSAGE_HH
