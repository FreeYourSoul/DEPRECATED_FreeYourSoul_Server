//
// Created by FyS on 27/04/17.
//

#ifndef FREESOULS_DEFAULTQUEUE_HH
#define FREESOULS_DEFAULTQUEUE_HH

#include <mutex>
#include <array>
#include <vector>
#include "QueueContainer.hh"

namespace fys {
    namespace mq {

        template <class TypeContainer>
        class LockingQueue {

        public:
            explicit LockingQueue(u_int sizeLfq) : _tail(0), _head(0), _sizeQueue(sizeLfq) {
                _queue.resize(sizeLfq);
            }

            const TypeContainer &pop() {
                TypeContainer topElem = _queue.at(_head);
                std::lock_guard<std::mutex> lock(_mutex);

                _head = getIndex(_head + 1);
                return topElem;
            }

            void push(const TypeContainer &elem) {
                _queue[_tail] = elem;
                {
                    std::lock_guard<std::mutex> lock(_mutex);
                    _tail = getIndex(_tail + 1);
                }
            }

        private:
            inline u_int getIndex(const u_int index) const {
                return index % _sizeQueue;
            }

        private:
            /**
             * Tail Point on the first non-used element of the queue
             */
            u_int _tail = 0;
            /**
             * Head Point on the first filled element of the queue
             */
            u_int _head = 0;

            u_int _sizeQueue;

            std::vector<TypeContainer> _queue;
            std::mutex _mutex;

        };

    }
}


#endif //FREESOULS_DEFAULTQUEUE_HH
