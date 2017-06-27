//
// Created by FyS on 27/06/17.
//

#ifndef FREESOULS_FYSBUSTEST_HH
#define FREESOULS_FYSBUSTEST_HH

#include <string>
#include <FysBus.hh>
#include <boost/test/test_tools.hpp>

namespace fys {
    namespace mq {
        namespace test {

            template <typename T, int SIZE_QUEUES>
            class FysBusTest : public fys::mq::FysBus<T, SIZE_QUEUES> {

            public:
                virtual ~FysBusTest() {}
                FysBusTest(const std::string &iniPath) : fys::mq::FysBus<T, SIZE_QUEUES>::FysBus(iniPath) { }

                void validateBusConfiguration(const unsigned int queueNumbers) {
                    BOOST_CHECK(queueNumbers == this->_queueRoutes.size());
                    BOOST_CHECK(queueNumbers == this->_queues.size());
                    for (u_int i = 0; i < this->_queueRoutes.size(); ++i) {
                        BOOST_CHECK(this->_queueRoutes.at(i).first.first < this->_queueRoutes.at(i).first.second);
                        for (u_int j = (i + 1); j < this->_queueRoutes.size(); ++j) {
                            BOOST_CHECK((this->_queueRoutes.at(i).first.first < this->_queueRoutes.at(j).first.first) &&
                                        (this->_queueRoutes.at(i).first.second < this->_queueRoutes.at(j).first.second) &&
                                        (this->_queueRoutes.at(i).first.second < this->_queueRoutes.at(j).first.first));
                        }
                    }
                }

            };

        }
    }
}



#endif //FREESOULS_FYSBUSTEST_HH
