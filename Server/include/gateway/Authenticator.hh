//
// Created by FyS on 31/08/17.
//

#ifndef FREESOULS_AUTHENTICATION_HH
#define FREESOULS_AUTHENTICATION_HH

#include <FySAuthenticationResponse.pb.h>

// forward declarations
namespace fys {
    namespace mq {
        template<typename T>
        class QueueContainer;
    }

    namespace gateway {
        class Gateway;
    }

    namespace pb {
        class LoginMessage;
        class FySMessage;
        class FySResponseMessage;
    }
}

namespace fys::gateway::buslistener {

    class Authenticator {

    public:
        enum { IndexInBus = 0 };

        Authenticator(std::shared_ptr<Gateway>&);

        void operator()(mq::QueueContainer<pb::FySMessage>);

    private:
        void authServer(const uint indexSession, pb::LoginMessage &&loginMessage);
        void authPlayer(const uint indexSession, pb::LoginMessage &&loginMessage);

        void sendErrorToServer(const uint indexSession, std::string &&error,
                               fys::pb::LoginErrorResponse::Type errorType);
        void sendErrorToPlayer(const uint indexSession, std::string &&error,
                               fys::pb::LoginErrorResponse::Type errorType);
        inline void createErrorMessage(fys::pb::FySResponseMessage &resp, std::string &&error,
                               fys::pb::LoginErrorResponse::Type errorType);

        pb::FySResponseMessage getAuthPlayerResponse(const uint indexSession, const GameServerInstance &gsi) const;
        fys::pb::FySMessage getNotifNewPlayerMessage(const uint indexSession, pb::LoginMessage &&loginMessage) const;

    private:
        std::shared_ptr<Gateway> _gtw;
    };

}


#endif //FREESOULS_AUTHENTICATION_HH
