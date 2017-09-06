//
// Created by FyS on 06/07/17.
//

#ifndef FREESOULS_AUTHMESSAGE_HH
#define FREESOULS_AUTHMESSAGE_HH

#include <string>
#include <HttpAuthClient.hh>
#include "Message.hh"

namespace fys {
    namespace network {

        class AuthMessage {

        public:
            enum {
                AUTH_PLAYER = 1,
                AUTH_SERVER = 2,
            };

        public:
            ~AuthMessage();
            AuthMessage();
            AuthMessage(const AuthMessage&);
            AuthMessage(AuthMessage&&);

            const std::string &getUser() const;
            const std::string &getPassword() const;
            const std::string &getToken() const;
            bool isServerAuth() const;

            bool initializePlayerAuth(Message &);
            bool initializeServerAuth(Message &);


        private:
            std::string _token;
            std::string _user;
            std::string _password;
            bool _isServerAuth;
        };

    }
}


#endif //FREESOULS_AUTHMESSAGE_HH
