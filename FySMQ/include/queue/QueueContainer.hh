//
// Created by FyS on 20/04/17.
//

#ifndef FREESOULS_QUEUECONTAINER_HH
#define FREESOULS_QUEUECONTAINER_HH

#include <atomic>
#include <sys/param.h>

namespace fys {
    namespace mq {

        /**
         * Container for a type for the LockFreeQueue @class fys::mq::LockFreeQueue
         */
        template <typename Type>
        class QueueContainer {
        public:
            ~QueueContainer() {}
            QueueContainer() : _routingKey(0) {}

            QueueContainer(const Type &container) : _routingKey(0), _contained(container) {}

            void setRoutingKey(const u_int8_t routingKey) {
                this->_routingKey = routingKey;
            }

            const u_int8_t getRoutingKey() const {
                return _routingKey;
            }

            const Type getContained() const {
                return _contained;
            }

        private:
            /**
             * Routing key for the {@class fys::mq::Bus}
             */
            u_int8_t   _routingKey;

            /**
             * Payload data to transfer via the queue
             */
            Type       _contained;
        };

    }
}

#endif //FREESOULS_QUEUECONTAINER_HH