#include <iostream>
#include <thread>
#include <boost/thread.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <Gateway.hh>
#include <Babble.hh>
#include <BabbleBusListener.hh>

void ok(int okok) {
    std::cout << "okok " << okok << std::endl;
}

int main(int argc, const char * const *argv)
{
    try {
        boost::asio::io_service ios;
        boost::asio::io_service::work work(ios);
        fys::gateway::Context ctx(argc, argv);
        fys::mq::FysBus<fys::network::Message, GATEWAY_BUS_QUEUES_SIZE>::ptr fysBus(
                new fys::mq::FysBus<fys::network::Message, GATEWAY_BUS_QUEUES_SIZE>(ctx.getBusIniFilePath()));
        fys::gateway::Gateway gtw(ctx, ios, fysBus);

        //Listeners
        fys::gateway::BabbleBusListener babbleListener(gtw.getGamerConnectionsPointer());
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
