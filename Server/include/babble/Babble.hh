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
        namespace buslistener {

            class Babble {
            public:
                enum { IndexInBus = 1 };

                ~Babble();

                Babble(const fys::network::SessionManager *const playerSessions);

                void operator()(fys::mq::QueueContainer<fys::network::Message> msg);

            private:
                void signInOnBabble(fys::network::BabbleMessage &&babbleMessage);
                void signOutFromBabble(fys::network::BabbleMessage &&babbleMessage);
                void sendMessage(fys::network::BabbleMessage &&babbleMessage);
                void whisperMessage(fys::network::BabbleMessage &&babbleMessage);
                bool isPlayerConnectedTo(const std::list<std::string> &playerConnected, const std::string &player);

            private:
                const network::SessionManager *_playerSessions;
                std::unordered_map<std::string, BabbleChannel> _channels;
                std::unordered_map<std::string, std::list<std::string> > _mapPlayerChannels;
                std::vector<std::string> _basicChannels;

            };

        }
    }
}

#endif //FREESOULS_BABBLE_HH
