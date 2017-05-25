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
#include "LockFreeQueue.hh"
#include "QueueContainer.hh"

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
            ~FysBus() {}
            FysBus(const std::string& iniPath) {
                try {
                    this->initializeBusFromIni(iniPath);
                }
                catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
            }

            void pushInBus(QueueContainer<T> message) {
                int routingKey = message.getRoutingKey();

                for (u_int i = 0; i < _queueRoutes.size(); ++i) {
                    if (routingKey >= _queueRoutes.at(i).first.first && routingKey <= _queueRoutes.at(i).first.second) {
                        _queues.at(_queueRoutes.at(i).second).push(message);
                        return;
                    }
                }
            }

            const QueueContainer<T> *popFromBus(const int routingKey) {
                for (u_int i = 0; i < _queueRoutes.size(); ++i) {
                    if (routingKey >= _queueRoutes.at(i).first.first && routingKey <= _queueRoutes.at(i).first.second)
                        return _queues.at(_queueRoutes.at(i).second).pop();
                }
                return NULL;
            }

        private:
            void initializeBusFromIni(const std::string &iniPath) {
                boost::property_tree::ptree pt;
                boost::property_tree::read_ini(iniPath, pt);
                int queueNumbers;

                queueNumbers = pt.get<int>(INIT_BUS_NB_QUEUE);
                std::cout << "Number of Queue in BUS :  " << pt.get<std::string>(INIT_BUS_NAME) << " -> "<<queueNumbers << std::endl;
                for (int i = 0; i < queueNumbers; ++i)
                    addQueueInBus(pt, i);
                validateBusConfiguration(queueNumbers);
            }

            void addQueueInBus(const boost::property_tree::ptree &pt, const int index) {
                std::string i = std::to_string(index + 1);
                int minParam = pt.get<int>(QUEUE_MIN(i));
                int maxParam = pt.get<int>(QUEUE_MAX(i));
                std::pair<int, int> queuePair(minParam, maxParam);
                std::pair<std::pair<int, int>, int> queuePairId(queuePair, index);
                LockFreeQueue<QueueContainer<T>, SIZE_QUEUES> queueToAdd;

                std::cout << "Queue " << i << ": " << pt.get<std::string>(QUEUE_NAME(i)) << " - MIN id: " << minParam << " - MAX id: " << maxParam << std::endl;
                _queueRoutes.push_back(queuePairId);
                _queues.push_back(queueToAdd);
            }

            void validateBusConfiguration(const int queueNumbers) {
                BOOST_ASSERT(queueNumbers == _queueRoutes.size());
                BOOST_ASSERT(queueNumbers == _queues.size());
                for (u_int i = 0; i < _queueRoutes.size(); ++i) {
                    std::pair<int, int> minMaxToCompare = _queueRoutes.at(i).first;
                    BOOST_ASSERT(minMaxToCompare.first < minMaxToCompare.second);
                    for (u_int j = (i + 1); j < _queueRoutes.size(); ++j) {
                        std::pair<int, int> minMax = _queueRoutes.at(j).first;
                        BOOST_ASSERT((minMaxToCompare.first < minMax.first) &&
                                     (minMaxToCompare.second < minMax.second) &&
                                     (minMaxToCompare.second < minMax.first));
                    }
                }
            }

        private:
            /**
             * list de pair
             *  [pair>int:int] : min:max
             *  [     int    ] : index in the _queues
             */
            std::vector<std::pair<std::pair<int, int>, u_int> > _queueRoutes;
            std::vector<LockFreeQueue<QueueContainer<T>, SIZE_QUEUES> > _queues;
        };

    }
}


#endif //FREESOULS_FYSBUS_HH
