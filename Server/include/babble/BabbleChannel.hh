//
// Created by FyS on 24/06/17.
//

#ifndef FREESOULS_BABBLECHANNEL_HH
#define FREESOULS_BABBLECHANNEL_HH

#include <string>
#include <list>

namespace fys {
    namespace gateway {

        class BabbleChannel {
        public:
            void connectOnChannel(const std::string &addedConnect);
            void disconnectFromChannel(const std::string &disconnect);

            const std::list<std::string> &getConnectedOnChannel() const;

        private:
            std::list<std::string> _connectedOnChannel;
        };

    }
}

#endif //FREESOULS_BABBLECHANNEL_HH
