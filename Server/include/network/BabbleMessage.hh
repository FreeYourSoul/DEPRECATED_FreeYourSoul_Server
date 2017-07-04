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
            ~BabbleMessage();
            BabbleMessage();

            fys::gateway::Babble::funcPtr initialize(const Message& message) const;

            const std::string &getAuthor() const;
            const std::string &getMessage() const;
            const std::string &getAddresse() const;
            bool isWhisper() const;
            bool isLogout() const;
            bool isLogin() const;

        private:
            void initializeBabbleLogin();
            void initializeBabbleLogout();
            void initializeBabbleMessage();

        private:
            fys::gateway::Babble::funcPtr _func;
            std::string _author;
            std::string _message;
            std::string _addresse;
            bool _isWhisper;
            bool _isLogout;
            bool _isLogin;

        };

    }
}

#endif //FREESOULS_BABBLEMESSAGE_HH
