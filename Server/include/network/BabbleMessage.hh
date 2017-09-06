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

        public:
            enum {
                LOGIN = 201,
                SEND = 202,
                WHISPER = 203,
                SIGNOUT = 204
            };

        public:
            ~BabbleMessage();
            BabbleMessage();
            BabbleMessage(const BabbleMessage&);
            BabbleMessage(BabbleMessage&&);

            const std::string &getAuthor() const;
            const std::string &getMessage() const;
            const std::string &getPassword() const;
            const std::string &getAddresse() const;
            bool isWhisper() const;

            bool initializeBabbleLogin(Message &);
            bool initializeBabbleLogout(Message &);
            bool initializeBabbleMessage(Message &);

        private:
            std::string _author;
            std::string _content;
            std::string _addressee;
            bool _isWhisper;

        };

    }
}

#endif //FREESOULS_BABBLEMESSAGE_HH
