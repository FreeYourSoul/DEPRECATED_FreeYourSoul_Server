#include <iostream>
#include <thread>
#include <boost/thread.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <Gateway.hh>
#include <HttpAuthClient.hh>
#include <BusListener.hh>
#include <Babble.hh>
#include <Authenticator.hh>

int main(int argc, const char * const *argv)
{
    try {
        boost::asio::io_service ios;
        boost::asio::io_service::work work(ios);
        fys::gateway::Context ctx(argc, argv);
        fys::mq::FysBus<fys::network::Message, fys::gateway::BUS_QUEUES_SIZE>::ptr fysBus(
                new fys::mq::FysBus<fys::network::Message, fys::gateway::BUS_QUEUES_SIZE>(ctx.getBusIniFilePath()));
        fys::gateway::Gateway gtw(ctx, ios, fysBus);
        fys::gateway::buslistener::Babble babble(gtw.getGamerConnectionsPointer());
        fys::gateway::buslistener::Authenticator authenticator(&gtw);

        fys::mq::BusListener<
                fys::gateway::buslistener::Babble,
                fys::mq::FysBus<fys::network::Message, fys::gateway::BUS_QUEUES_SIZE> >
                    babbleListener(babble);
        babbleListener.launchListenThread(fysBus);

        std::cout << ctx << std::endl;
        gtw.runPlayerAccept();
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
