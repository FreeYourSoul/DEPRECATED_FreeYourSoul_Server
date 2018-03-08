//
// Created by FyS on 24/06/17.
//

#ifndef FREESOULS_BABBLE_HH
#define FREESOULS_BABBLE_HH

#include <string>
#include <unordered_map>
#include "BabbleChannel.hh"

// forward declarations
namespace fys {
    namespace mq {
        template <typename T>
        class QueueContainer;
    }

    namespace gateway {
        class Gateway;
    }

    namespace network {

    }

    namespace pb {
        class FySMessage;
        class FySBabbleMessage;
    }
}

namespace fys::gateway::buslistener {

    class Babble {
    public:
        enum { IndexInBus = 1 };

        explicit Babble(std::shared_ptr<Gateway>&);

        void operator()(fys::mq::QueueContainer<fys::pb::FySMessage>);

    private:
        void signInOnBabble(pb::FySBabbleMessage &&babbleMessage);
        void signOutFromBabble(pb::FySBabbleMessage &&babbleMessage);
        void sendMessage(pb::FySBabbleMessage &&babbleMessage);
        void whisperMessage(pb::FySBabbleMessage &&babbleMessage);
        bool isPlayerConnectedTo(const std::list<std::string> &playerConnected, const std::string &player);

    private:
        std::shared_ptr<Gateway> _gtw;
        std::unordered_map<std::string, BabbleChannel> _channels;
        std::unordered_map<std::string, std::list<std::string> > _mapPlayerChannels;
        std::vector<std::string> _basicChannels;

    };

}

#endif //FREESOULS_BABBLE_HH
