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
                virtual ~FysBusTest() = default;
                explicit FysBusTest(const int size) : fys::mq::FysBus<T, SIZE_QUEUES>::FysBus(size) { }

                void validateBusConfiguration(const unsigned int queueNumbers) {
                    BOOST_CHECK(queueNumbers == this->_queues.size());
                }

            };

        }
    }
}



#endif //FREESOULS_FYSBUSTEST_HH
