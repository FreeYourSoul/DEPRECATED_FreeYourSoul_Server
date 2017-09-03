#include <iostream>
#include <thread>
#include <Gateway.hh>
#include <HttpAuthClient.hh>
#include <BusListener.hh>
#include <Babble.hh>
#include <Authenticator.hh>
#include <TokenGenerator.hh>

using namespace fys::mq;
using namespace fys::gateway;
using namespace fys::network;

using BabbleBusListener = BusListener <buslistener::Babble, FysBus<Message, BUS_QUEUES_SIZE>>;
using AuthBusListener = BusListener <buslistener::Authenticator, FysBus<Message, BUS_QUEUES_SIZE>>;


int main(int argc, const char * const *argv)
{
    try {
        boost::asio::io_service ios;
        boost::asio::io_service::work work(ios);
        Context ctx(argc, argv);
        FysBus<fys::network::Message, BUS_QUEUES_SIZE>::ptr fysBus(
                new FysBus<Message, BUS_QUEUES_SIZE>(ctx.getBusIniFilePath()));
        Gateway::ptr gtw = std::make_shared<Gateway>(ctx, ios, fysBus);
        buslistener::Babble babble(gtw->getGamerConnectionsPointer());
        buslistener::Authenticator authenticator(gtw);
        BabbleBusListener babbleListener(babble);
        AuthBusListener authenticatorListener(authenticator);

        authenticatorListener.launchListenThread(fysBus);
        babbleListener.launchListenThread(fysBus);
        std::cout << ctx << std::endl;
        std::cout << fys::utils::TokenGenerator::getInstance()->generate() << std::endl;
        gtw->runPlayerAccept();
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
