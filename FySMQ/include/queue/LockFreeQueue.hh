//
// Created by FyS on 20/04/17.
//

#ifndef FREESOULS_LOCKFREEQUEUE_HH
#define FREESOULS_LOCKFREEQUEUE_HH

#include <array>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <optional>
#include "QueueContainer.hh"

namespace fys {
    namespace mq {

        template <class TypeContainer, int SizeLFQ>
        class LockFreeQueue {

        public:
            ~LockFreeQueue() = default;
            LockFreeQueue() : _tail(0), _maxReadTail(0), _head(0), _isLocked(true), _isLockingWhenEmpty(true) {}

            std::optional<TypeContainer> pop() {
                u_int currentReadTail = getIndex(_maxReadTail.load(std::memory_order_relaxed));
                u_int currentHead = getIndex(_head);

                if (currentHead < currentReadTail) {
                    return _queue[_head++];
                }
                lockCondVar();
                return std::optional<TypeContainer> {};
            }

            void push(const TypeContainer &elem) {
                u_int currentTail = _tail.fetch_add(1, std::memory_order_relaxed);
                u_int indexNewElem = getIndex(currentTail);
                u_int tstValue;

                _queue[indexNewElem] = elem;
                do {
                    tstValue = currentTail;
                } while (!_maxReadTail.compare_exchange_weak(tstValue, currentTail + 1));
                if (_isLocked) {
                    _isLocked = false;
                    _cv.notify_all();
                }
            }

            void lockCondVar() {
                if (_isLockingWhenEmpty) {
                    std::unique_lock<std::mutex> lck(_mutex);
                    _isLocked = true;
                    _cv.wait(lck, [&]{return !_isLocked;});
                }
            }

            void setLockingWhenEmpty(const bool _isLockingWhenEmpty) {
                LockFreeQueue::_isLockingWhenEmpty = _isLockingWhenEmpty;
            }

            bool isLockingWhenEmpty() const {
                return _isLockingWhenEmpty;
            }

        private:
            inline u_int getIndex(const u_int index) const {
                return index % SizeLFQ;
            }

        private:
            std::atomic_uint _tail;
            std::atomic_uint _maxReadTail;
            u_int            _head;
            bool             _isLocked;
            bool             _isLockingWhenEmpty;

            std::mutex _mutex;
            std::condition_variable _cv;

            std::array<TypeContainer, SizeLFQ> _queue;
        };

    }
}

#endif //FREESOULS_LOCKFREEQUEUE_HH
