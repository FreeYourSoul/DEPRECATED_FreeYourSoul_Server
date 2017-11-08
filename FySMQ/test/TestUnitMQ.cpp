//
// Created by FyS on 16/06/17.
//

#define BOOST_TEST_MODULE test_bus
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>
#include <experimental/optional>
#include "FysBusTest.hh"

/**
 * ------------------------------------------------------
 *  Bus Initialisation test------------------------------
 * ------------------------------------------------------
 */
BOOST_AUTO_TEST_CASE( test_bus_ini )
{
    fys::mq::test::FysBusTest<std::string, 100> bus(2);
    bus.validateBusConfiguration(2);
}

BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES( test_bus_ini_error1, 1 )
BOOST_AUTO_TEST_CASE( test_bus_ini_error1 )
{
    fys::mq::test::FysBusTest<std::string, 100> bus(1);
    bus.validateBusConfiguration(2);
}

BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES( test_bus_ini_error2, 1 )
BOOST_AUTO_TEST_CASE( test_bus_ini_error2 )
{
    fys::mq::test::FysBusTest<std::string, 100> bus(2);
    bus.validateBusConfiguration(3);
}

/**
 *------------------------------------------------------
 * Bus exections test ----------------------------------
 *------------------------------------------------------
 */
fys::mq::LockFreeQueue<fys::mq::QueueContainer<std::string>, 5000> *lockFreeQueue;
int readValues;

void addinlockfreequeue(const fys::mq::QueueContainer<std::string> &container) {

    for (int i = 0; i < 1500; ++i) {
        lockFreeQueue->push(container);
    }
}

void readLockFreeQueue() {
    for (int i = 0; i < 5000; ++i) {
        usleep(100);
        if (lockFreeQueue->pop()) {
            ++readValues;
        }
    }
}

void initTestExecution() {
    lockFreeQueue = new fys::mq::LockFreeQueue<fys::mq::QueueContainer<std::string>, 5000>();
    lockFreeQueue->setLockingWhenEmpty(false);
    readValues = 0;
}

void cleanTestExecution() {
    if (lockFreeQueue != nullptr) {
        delete(lockFreeQueue);
        lockFreeQueue = nullptr;
    }
}

BOOST_AUTO_TEST_CASE( test_queue_exec ) {
    fys::mq::QueueContainer<std::string> c1("A");
    fys::mq::QueueContainer<std::string> c2("B");
    fys::mq::QueueContainer<std::string> c3("C");

    std::cout << "begin Protobuff exec" << std::endl;
    c1.setOpCodeMsg(42);
    c2.setOpCodeMsg(43);
    c3.setOpCodeMsg(44);
    initTestExecution();
    boost::thread workerRead(readLockFreeQueue);
    boost::thread w1([this, &c1]() { addinlockfreequeue(c1); });
    boost::thread w2([this, &c2]() { addinlockfreequeue(c2); });
    boost::thread w3([this, &c3]() { addinlockfreequeue(c3); });

    w1.join();
    w2.join();
    w3.join();
    workerRead.join();
    cleanTestExecution();
    std::cout << "end Protobuff exec : readValue = " << readValues << std::endl;
    BOOST_CHECK(readValues == 4500);
}