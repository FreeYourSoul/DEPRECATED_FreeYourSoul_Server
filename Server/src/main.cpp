#include <iostream>
#include <thread>
#include <boost/thread.hpp>
#include <boost/timer/timer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include "LockingQueue.hh"
#include "LockFreeQueue.hh"

fys::mq::LockingQueue<fys::mq::QueueContainer<std::string> > lockingQueue(5000);
fys::mq::LockFreeQueue<fys::mq::QueueContainer<std::string>, 5000> lockFreeQueue;

void addinlockingqueue(const fys::mq::QueueContainer<std::string> &container) {

    for (int i = 0; i < 1500; ++i) {
        lockingQueue.push(container);
    }
}

void addinlockfreequeue(const fys::mq::QueueContainer<std::string> &container) {

    for (int i = 0; i < 1500; ++i) {
        lockFreeQueue.push(container);
    }
}

void readLockFreeQueue() {
    int data = 0;

    for (int i = 0; data < 4500; ++i) {
        fys::mq::QueueContainer<std::string> *container;

        container = lockFreeQueue.pop();
        if (container) {
            std::cout<< "poped data n." << ++data << " value " << container->getContained() << std::endl;
        }
        else
            std::cout<< "queue empty" << std::endl;
    }
}

void test1() {
    fys::mq::QueueContainer<std::string> c1("A");
    fys::mq::QueueContainer<std::string> c2("B");
    fys::mq::QueueContainer<std::string> c3("C");

    boost::thread w1(boost::bind(addinlockingqueue, c1));
    boost::thread w2(boost::bind(addinlockingqueue, c2));
    boost::thread w3(boost::bind(addinlockingqueue, c3));

    w1.join();
    w2.join();
    w3.join();
}


void test2() {
    fys::mq::QueueContainer<std::string> c1("A");
    fys::mq::QueueContainer<std::string> c2("B");
    fys::mq::QueueContainer<std::string> c3("C");

    boost::thread w1(boost::bind(addinlockfreequeue, c1));
    boost::thread w2(boost::bind(addinlockfreequeue, c2));
    boost::thread w3(boost::bind(addinlockfreequeue, c3));

    w1.join();
    w2.join();
    w3.join();
}

void test3() {
    fys::mq::QueueContainer<std::string> c1("A");
    fys::mq::QueueContainer<std::string> c2("B");
    fys::mq::QueueContainer<std::string> c3("C");

    boost::thread workerRead(readLockFreeQueue);
    boost::thread w1(boost::bind(addinlockfreequeue, c1));


    w1.join();
    sleep(5);
    boost::thread w2(boost::bind(addinlockfreequeue, c2));
    boost::thread w3(boost::bind(addinlockfreequeue, c3));
    w2.join();
    w3.join();
    workerRead.join();

}

union {
    unsigned int integer;
    unsigned char byte[4];
} temp32bitint;

class test {

public:
    test() {
        opCode = 42;        //00000000 00000000 00000000 00101010
        sizeStr = 1337;     //00000000 00000000 00000101 00111001
        str[0] = 10;        //00001010
        str[1] = 100;       //01100100
        str[2] = 107;       //01101011
    }

    unsigned int opCode;
    unsigned int sizeStr;
    unsigned char str[3];

    void load(unsigned char str[100]) {
        temp32bitint.byte[0] = str[0];
        temp32bitint.byte[1] = str[1];
        temp32bitint.byte[2] = str[2];
        temp32bitint.byte[3] = str[3];
        opCode = temp32bitint.integer;
    }
};


class session
{
public:
    session(boost::asio::io_service& io_service)
            : socket_(io_service)
    {
    }

    boost::asio::ip::tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        socket_.async_read_some(boost::asio::buffer(header_buf_in, 99),
                                boost::bind(&session::handle_read, this,
                                            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

private:
    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred)
    {
        if (!error)
        {
            std::cout << bytes_transferred << std::endl;
            data_.load(header_buf_in);
            std::cout << header_buf_in << std::endl;
            std::cout << "opCode " << data_.opCode <<std::endl;
        }
        else
        {
            std::cout << "error : "  << error.message()<<std::endl;
            delete this;
        }
    }

    void handle_write(const boost::system::error_code& error)
    {

    }

    boost::asio::ip::tcp::socket socket_;
    unsigned char header_buf_in[100];
    test data_;
};

class server
{
public:
    server(boost::asio::io_service& io_service, short port)
            : io_service_(io_service),
              acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        start_accept();
    }

private:
    void start_accept()
    {
        session* new_session = new session(io_service_);
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(session* new_session,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            new_session->start();
        }
        else
        {
            delete new_session;
        }

        start_accept();
    }

    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
};


void simpleServerCall() {
    boost::asio::io_service io_service;
    server s(io_service, 4242);
    std::cout << "server start"<< std::endl;
    io_service.run();
}

void test4() {
    test message;

    boost::thread t(simpleServerCall);
    sleep(5);
    boost::asio::io_service ios;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4242);

    boost::asio::ip::tcp::socket socket(ios);

    socket.connect(endpoint);

    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer((unsigned char *)&message, sizeof(message)), error);
    std::cout << error.message() << std::endl;
    socket.close();
}

int main(void)
{
    boost::timer::cpu_timer cpu_timer;
    test4();
    std::cout << std::endl << "timer : " << cpu_timer.format() << std::endl;
    return 0;
}
