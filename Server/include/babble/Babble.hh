//
// Created by FyS on 24/06/17.
//

#ifndef FREESOULS_BABBLE_HH
#define FREESOULS_BABBLE_HH

#include <map>
#include <string>
#include <unordered_map>
#include <SessionManager.hh>
#include <Message.hh>
#include "BabbleChannel.hh"

namespace fys {
    namespace network {
        class BabbleMessage;
    }

    namespace gateway {

        class Babble {

        public:
            typedef void (fys::gateway::Babble::*funcPtr)(const fys::network::BabbleMessage &);

            ~Babble();
            Babble(const network::SessionManager *playerSessions);

            void signInOnBabble(const std::string &tokenSignIn);
            void signOutFromBabble(const std::string &tokenSignOut, const std::string &channel);
            void sendMessage(const fys::network::BabbleMessage &babbleMessage);
            void whisperMessage(const fys::network::BabbleMessage &babbleMessage);

        private:
            bool isPlayerConnectedTo(std::list<std::string> &playerConnected, const std::string &player);

        private:
            const network::SessionManager *_playerSessions;
            std::unordered_map<std::string, BabbleChannel> _channels;
            std::unordered_map<std::string, std::list<std::string> > _mapPlayerChannels;
            std::vector<std::string> _basicChannels;

        };

    }
}

#endif //FREESOULS_BABBLE_HH
