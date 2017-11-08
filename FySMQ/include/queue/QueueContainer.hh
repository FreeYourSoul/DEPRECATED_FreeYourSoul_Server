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
            QueueContainer() : _opCodeMsg(0), _indexSession(0) {}
            explicit QueueContainer(const Type &container) : _opCodeMsg(0), _indexSession(0), _contained(container) {
            }

            friend std::ostream &operator<<(std::ostream &os, const QueueContainer &container) {
                os << "_opCodeMsg: " << container._opCodeMsg << " _tokenUser: " << container._indexSession << std::endl;
                return os;
            }

            void setOpCodeMsg(const unsigned short opCodeMsg) {
                this->_opCodeMsg = opCodeMsg;
            }

            unsigned short getOpCodeMsg() const {
                return _opCodeMsg;
            }

            Type &getContained() {
                return _contained;
            }

            const Type &getContained() const {
                return _contained;
            }

            uint getIndexSession() const {
                return _indexSession;
            }

            void setIndexSession(const uint indexSession) {
                this->_indexSession = indexSession;
            }

            void setContained(const Type &contained) {
                this->_contained = contained;
            }

        private:
            /**
             * OpCode of the message for the {@class fys::mq::Bus} to redirect it to the correct queue
             */
            unsigned short _opCodeMsg = 0;

            /**
             * index position of the session (information used to get back the connection for the answer)
             */
            uint _indexSession = 0;

            /**
             * Payload data to transfer via the queue
             */
            Type _contained;
        };

    }
}

#endif //FREESOULS_QUEUECONTAINER_HH