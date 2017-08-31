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
        template <class Type>
        class QueueContainer {
        public:
            ~QueueContainer() {}
            QueueContainer() : _opCodeMsg(0) {}

            QueueContainer(const Type &container) : _opCodeMsg(0), _contained(container) {}

            friend std::ostream &operator<<(std::ostream &os, const QueueContainer &container) {
                os << "_opCodeMsg: " << container._opCodeMsg << " _tokenUser: " << container._tokenUser << std::endl;
                return os;
            }

            void setOpCodeMsg(const unsigned short opCodeMsg) {
                this->_opCodeMsg = opCodeMsg;
            }

            unsigned short getOpCodeMsg() const {
                return _opCodeMsg;
            }

            const Type &getContained() const {
                return _contained;
            }

            const std::string &get_tokenUser() const {
                return _tokenUser;
            }

            void setTokenUser(const std::string &_tokenUser) {
                QueueContainer::_tokenUser = _tokenUser;
            }

            void setContained(const Type &contained) {
                this->_contained = contained;
            }

        private:
            /**
             * OpCode of the message for the {@class fys::mq::Bus} to redirect it to the correct queue
             */
            unsigned short _opCodeMsg;

            /**
             * Token, used to route the message to the client to reply to
             * Set to NULL only during authentications
             */
            std::string _tokenUser;

            /**
             * Payload data to transfer via the queue
             */
            Type _contained;
        };

    }
}

#endif //FREESOULS_QUEUECONTAINER_HH