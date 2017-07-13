//
// Created by FyS on 03/07/17.
//

#ifndef FREESOULS_BABBLEMESSAGE_HH
#define FREESOULS_BABBLEMESSAGE_HH

#include <Babble.hh>
#include "Message.hh"

namespace fys {
    namespace network {

        enum BabbleOpCode {
            LOGIN = 301,
            SEND = 302,
            WHISPER = 303,
            SIGNOUT = 304
        };

        class BabbleMessage {

        public:
            ~BabbleMessage();
            BabbleMessage();

            fys::gateway::Babble::funcPtr initialize(const Message& message);

            const std::string &getAuthor() const;
            const std::string &getMessage() const;
            const std::string &getPassword() const;
            const std::string &getAddresse() const;
            bool isWhisper() const;
            bool isLogout() const;
            bool isLogin() const;

        private:
            bool initializeBabbleLogin(const unsigned char *string);
            bool initializeBabbleLogout(const unsigned char *string);
            bool initializeBabbleMessage(const unsigned char *string);

        private:
            fys::gateway::Babble::funcPtr _func;
            std::string _author;
            std::string _content;
            std::string _addressee;
            bool _isWhisper;
            bool _isLogout;
            bool _isLogin;

        };

    }
}

#endif //FREESOULS_BABBLEMESSAGE_HH
