//
// Created by FyS on 25/05/17.
//

#ifndef FREESOULS_IBUSLISTENER_HH
#define FREESOULS_IBUSLISTENER_HH

#include <sys/types.h>

namespace fys {
    namespace mq {

        class IBusListener {
        public:
            virtual void listen() = 0;
            virtual void setBusRoutingKey(const u_int) = 0;
        };

    }
}

#endif //FREESOULS_IBUSLISTENER_HH
