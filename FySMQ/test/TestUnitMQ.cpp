//
// Created by FyS on 16/06/17.
//

#define BOOST_TEST_MODULE test_bus
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>
#include "FysBusTest.hh"

/**
 * ------------------------------------------------------
 *  Bus Initialisation test------------------------------
 * ------------------------------------------------------
 */

BOOST_AUTO_TEST_CASE( test_bus_ini )
{
    fys::mq::test::FysBusTest<std::string, 100> bus("/home/FyS/ClionProjects/FreeYourSoul_Server/FySMQ/resource/test_bus_inifile.ini");
    bus.validateBusConfiguration(2);
}

BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES( test_bus_ini_error1, 2 )
BOOST_AUTO_TEST_CASE( test_bus_ini_error1 )
{
    fys::mq::test::FysBusTest<std::string, 100> bus("/home/FyS/ClionProjects/FreeYourSoul_Server/FySMQ/resource/test_bus_inifile_error1.ini");
    bus.validateBusConfiguration(2);
}

BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES( test_bus_ini_error2, 2 )
BOOST_AUTO_TEST_CASE( test_bus_ini_error2 )
{
    fys::mq::test::FysBusTest<std::string, 100> bus("/home/FyS/ClionProjects/FreeYourSoul_Server/FySMQ/resource/test_bus_inifile_error2e.ini");
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
        fys::mq::QueueContainer<std::string> *container;

        container = lockFreeQueue->pop();
        usleep(100);
        if (container != NULL) {
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

    std::cout << "begin test exec" << std::endl;
    c1.setOpCodeMsg(42);
    c2.setOpCodeMsg(43);
    c3.setOpCodeMsg(44);
    initTestExecution();
    boost::thread workerRead(readLockFreeQueue);
    boost::thread w1(boost::bind(addinlockfreequeue, c1));
    boost::thread w2(boost::bind(addinlockfreequeue, c2));
    boost::thread w3(boost::bind(addinlockfreequeue, c3));

    w1.join();
    w2.join();
    w3.join();
    workerRead.join();
    cleanTestExecution();
    std::cout << "end test exec : readValue = " << readValues << std::endl;
    BOOST_CHECK(readValues == 4500);
}