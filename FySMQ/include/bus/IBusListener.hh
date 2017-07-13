//
// Created by FyS on 25/05/17.
//

#ifndef FREESOULS_IBUSLISTENER_HH
#define FREESOULS_IBUSLISTENER_HH

#include <string>
#include <sys/types.h>
#include "FysBus.hh"

namespace fys {
    namespace mq {

        template <class  BusType>
        class IBusListener {
        public:
            virtual void listen(BusType &fysBus) = 0;
            virtual void setBusRoutingKey(const u_int) = 0;
        };

    }
}

#endif //FREESOULS_IBUSLISTENER_HH
