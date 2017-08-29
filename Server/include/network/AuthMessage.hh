//
// Created by FyS on 06/07/17.
//

#ifndef FREESOULS_AUTHMESSAGE_HH
#define FREESOULS_AUTHMESSAGE_HH

#include <string>
#include <http/HttpAuthClient.hh>
#include "Message.hh"

namespace fys {
    namespace network {

        class AuthMessage {

            enum {
                AUTH_PLAYER = 001
            };

        public:
            ~AuthMessage();
            AuthMessage();

            fys::network::http::HttpAuthClient::funcPtr initialize(const Message& message);

            const std::string &get_user() const;
            const std::string &get_password() const;
            const std::string &get_token() const;
            void set_user(const std::string &_user);
            void set_password(const std::string &_password);
            void set_token(const std::string &_token);

        private:
            std::string _user;
            std::string _password;
            std::string _token;
        };

    }
}


#endif //FREESOULS_AUTHMESSAGE_HH
