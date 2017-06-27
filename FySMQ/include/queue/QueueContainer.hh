//
// Created by FyS on 20/04/17.
//

#ifndef FREESOULS_QUEUECONTAINER_HH
#define FREESOULS_QUEUECONTAINER_HH

#include <atomic>
#include <sys/param.h>
#include <string>
#include <ostream>

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

            friend std::ostream &operator<<(std::ostream &os, const QueueContainer &container) {
                os << "_routingKey: " << container._routingKey << " _tokenUser: " << container._tokenUser << std::endl;
                return os;
            }

            void setRoutingKey(const u_int8_t routingKey) {
                this->_routingKey = routingKey;
            }

            const u_int8_t getRoutingKey() const {
                return _routingKey;
            }

            const Type getContained() const {
                return _contained;
            }

            const std::string &get_tokenUser() const {
                return _tokenUser;
            }

            void set_tokenUser(const std::string &_tokenUser) {
                QueueContainer::_tokenUser = _tokenUser;
            }

        private:
            /**
             * Routing key for the {@class fys::mq::Bus}
             */
            u_int8_t   _routingKey;

            /**
             * Token, used to route the message to the client to reply to
             * Set to NULL only during authentications
             */
            std::string _tokenUser;

            /**
             * Payload data to transfer via the queue
             */
            Type       _contained;
        };

    }
}

#endif //FREESOULS_QUEUECONTAINER_HH