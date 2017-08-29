#include <iostream>
#include <thread>
#include <boost/thread.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <Gateway.hh>
#include <Babble.hh>
#include <http/HttpAuthClient.hh>
#include <BusListener.hh>

void ok() {

}

class FunctorTest {
public:
    FunctorTest() {}

    FunctorTest &operator()(fys::mq::QueueContainer<fys::network::Message> *msg) {
        std::cout << "inside : " << msg->getContained().getOpCode() << std::endl;
        return *this;
    }
};

int main(int argc, const char * const *argv)
{
    ok();
    try {
        boost::asio::io_service ios;
        boost::asio::io_service::work work(ios);
        fys::gateway::Context ctx(argc, argv);
        fys::mq::FysBus<fys::network::Message, fys::gateway::BUS_QUEUES_SIZE>::ptr fysBus(
                new fys::mq::FysBus<fys::network::Message, fys::gateway::BUS_QUEUES_SIZE>(ctx.getBusIniFilePath()));
        fys::gateway::Gateway gtw(ctx, ios, fysBus);

        FunctorTest test;
        fys::mq::BusListener<FunctorTest, fys::mq::FysBus<fys::network::Message, fys::gateway::BUS_QUEUES_SIZE> > listenertest(0, test);
        listenertest.launchListenThread(fysBus);

        std::cout << ctx << std::endl;
        gtw.runPlayerAccept();
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
