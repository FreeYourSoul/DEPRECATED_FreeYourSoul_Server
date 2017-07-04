//
// Created by FyS on 21/05/17.
//

#ifndef FREESOULS_FYSBUS_HH
#define FREESOULS_FYSBUS_HH

#include <string>
#include <vector>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <LockFreeQueue.hh>
#include <QueueContainer.hh>

#define INIT_BUS_NB_QUEUE "bus.number_queue"
#define INIT_BUS_NAME "bus.name"
#define BUS_QUEUE(n) std::string("queue") + n
#define QUEUE_NAME(n) BUS_QUEUE(n) + ".name"
#define QUEUE_MIN(n) BUS_QUEUE(n) + ".min"
#define QUEUE_MAX(n) BUS_QUEUE(n) + ".max"

namespace fys {
    namespace mq {

        template <typename T, int SIZE_QUEUES>
        class FysBus {

        public:
            typedef boost::shared_ptr<FysBus<T, SIZE_QUEUES> > ptr;

            ~FysBus() { // TODO delete correctly the _queues
//                int toDelete = -1;
//
//                for (int i = 0; i < _queues.size(); ++i) {
//                    if (toDelete == -1) {
//                        delete(_queues.at(toDelete));
//                        _queues.erase(toDelete);
//                    }
//                    toDelete = i;
//                }
            }
            FysBus(const std::string& iniPath) {
                try {
                    this->initializeBusFromIni(iniPath);
                }
                catch (std::exception &e) {
                    std::cout << "FysBus Exception at initialization : " << e.what() << std::endl;
                }
            }

            void pushInBus(QueueContainer<T> message) {
                int opCodeMsg = message.getOpCodeMsg();

                for (u_int8_t i = 0; i < _queueRoutes.size(); ++i) {
                    if (opCodeMsg >= _queueRoutes.at(i).first.first && opCodeMsg <= _queueRoutes.at(i).first.second) {
                        _queues.at(_queueRoutes.at(i).second)->push(message);
                        return;
                    }
                }
            }

            QueueContainer<T> *popFromBus(const int indexQueueInBus) {
                if (indexQueueInBus < _queueRoutes.size() && indexQueueInBus < _queues.size()) {
                    return _queues.at(indexQueueInBus)->pop();
                }
                return NULL;
            }

            u_int8_t getRoutingKeyFromOpCode(const unsigned short opCode) const {
                for (int i = 0; i < _queueRoutes.size(); ++i)
                    if (opCode >= _queueRoutes.at(i).first.first && opCode < _queueRoutes.at(i).first.second)
                        return _queueRoutes.at(i).second;
                return _queueRoutes.size() + 1;
            }

        private:
            void initializeBusFromIni(const std::string &iniPath) {
                boost::property_tree::ptree pt;
                boost::property_tree::read_ini(iniPath, pt);
                int queueNumbers;

                queueNumbers = pt.get<int>(INIT_BUS_NB_QUEUE);
                for (int i = 0; i < queueNumbers; ++i)
                    addQueueInBus(pt, i);
            }

            void addQueueInBus(const boost::property_tree::ptree &pt, const int index) {
                std::string i = std::to_string(index + 1);
                int minParam = pt.get<int>(QUEUE_MIN(i));
                int maxParam = pt.get<int>(QUEUE_MAX(i));
                std::pair<int, int> queuePair(minParam, maxParam);
                std::pair<std::pair<int, int>, int> queuePairId(queuePair, index);
                LockFreeQueue<QueueContainer<T>, SIZE_QUEUES> *queueToAdd = new LockFreeQueue<QueueContainer<T>, SIZE_QUEUES>();

                std::cout << "Queue " << i << ":" << pt.get<std::string>(QUEUE_NAME(i)) << " - MIN id: " << minParam << " - MAX id: " << maxParam << " - isLockingWhenEmpty: " << queueToAdd->isLockingWhenEmpty() << std::endl;
                _queueRoutes.push_back(queuePairId);
                _queues.push_back(queueToAdd);
            }


        protected:
            /**
             * pair list
             *
             *  [pair>int:int] : min:max
             *  [     int    ] : index in the _queues
             */
            std::vector<std::pair<std::pair<int, int>, int> > _queueRoutes;
            std::vector<LockFreeQueue<QueueContainer<T>, SIZE_QUEUES> *> _queues;
        };

    }
}


#endif //FREESOULS_FYSBUS_HH
