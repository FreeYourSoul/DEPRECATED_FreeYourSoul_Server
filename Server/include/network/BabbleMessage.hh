//
// Created by FyS on 03/07/17.
//

#ifndef FREESOULS_BABBLEMESSAGE_HH
#define FREESOULS_BABBLEMESSAGE_HH

#include <Babble.hh>
#include "Message.hh"

namespace fys {
    namespace network {

        class BabbleMessage {

            enum {
                LOGIN = 201,
                SEND = 202,
                WHISPER = 203,
                SIGNOUT = 204
            };

        public:
            BabbleMessage();
            ~BabbleMessage();

            fys::gateway::Babble::funcPtr initialize(const Message& message);

            const std::string &getAuthor() const;
            const std::string &getMessage() const;
            const std::string &getPassword() const;
            const std::string &getAddresse() const;
            bool isWhisper() const;

        private:
            bool initializeBabbleLogin(const Message &string);
            bool initializeBabbleLogout(const Message &string);
            bool initializeBabbleMessage(const Message &string);

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
