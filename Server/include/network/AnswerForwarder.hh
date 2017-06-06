//
// Created by FyS on 30/05/17.
//

#ifndef FREESOULS_ANSWERFORWARDER_HH
#define FREESOULS_ANSWERFORWARDER_HH

#include <list>
#include "SessionManager.hh"

namespace fys {
    namespace network {

        class AnswerForwarder {

        public:
            ~AnswerForwarder();
            AnswerForwarder(SessionManager&);

            void forwardMessage(const Message& msg, const std::list<std::string> &gamerTokens) const;

        private:
            SessionManager   &_gamersConnections;

        };

    }
}


#endif //FREESOULS_ANSWERFORWARDER_HH
