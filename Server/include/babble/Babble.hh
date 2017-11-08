//
// Created by FyS on 24/06/17.
//

#ifndef FREESOULS_BABBLE_HH
#define FREESOULS_BABBLE_HH

#include <map>
#include <string>
#include <unordered_map>
#include <SessionManager.hh>
#include <FySGtwMessage.pb.h>
#include <FySBabbleMessage.pb.h>
#include <Gateway.hh>
#include "BabbleChannel.hh"

namespace fys {

    namespace gateway {
        namespace buslistener {

            class Babble {
            public:
                enum { IndexInBus = 1 };

                explicit Babble(Gateway::ptr&);

                void operator()(fys::mq::QueueContainer<fys::pb::FySGtwMessage> msg);

            private:
                void signInOnBabble(fys::pb::FySBabbleMessage &&babbleMessage);
                void signOutFromBabble(fys::pb::FySBabbleMessage &&babbleMessage);
                void sendMessage(fys::pb::FySBabbleMessage &&babbleMessage);
                void whisperMessage(fys::pb::FySBabbleMessage &&babbleMessage);
                bool isPlayerConnectedTo(const std::list<std::string> &playerConnected, const std::string &player);

            private:
                Gateway::ptr _gtw;
                std::unordered_map<std::string, BabbleChannel> _channels;
                std::unordered_map<std::string, std::list<std::string> > _mapPlayerChannels;
                std::vector<std::string> _basicChannels;

            };

        }
    }
}

#endif //FREESOULS_BABBLE_HH
