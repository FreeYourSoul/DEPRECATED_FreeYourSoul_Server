//
// Created by FyS on 24/06/17.
//

#ifndef FREESOULS_BABBLE_HH
#define FREESOULS_BABBLE_HH

#include <map>
#include <string>
#include <Message.hh>
#include <SessionManager.hh>
#include "BabbleChannel.hh"

namespace fys {
    namespace gateway {

        class Babble {

        public:
            ~Babble();
            Babble(const network::SessionManager *playerSessions);

            void signInOnBabble(const std::string &tokenSignIn);
            void signOutFromBabble(const std::string &tokenSignOut);
            void sendMessage(const network::Message &babbleMessage) const;
            void whisperMessage(const network::Message message) const;

        private:
            const network::SessionManager *_playerSessions;
            std::map<std::string, BabbleChannel> _channels;


        };

    }
}

#endif //FREESOULS_BABBLE_HH
