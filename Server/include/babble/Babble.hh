//
// Created by FyS on 24/06/17.
//

#ifndef FREESOULS_BABBLE_HH
#define FREESOULS_BABBLE_HH

#include <map>
#include <string>
#include <Message.hh>
#include "BabbleChannel.hh"

namespace fys {
    namespace gateway {

        class Babble {

        public:
            ~Babble();
            Babble();

            void signInOnBabble(const std::string &tokenSignIn);
            void signOutFromBabble(const std::string &tokenSignOut);
            void sendMessage(const network::Message &babbleMessage) const;

        private:
            std::map<std::string, BabbleChannel> _channels;

        };

    }
}

#endif //FREESOULS_BABBLE_HH
