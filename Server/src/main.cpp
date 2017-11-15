#include <iostream>
#include <thread>
#include <Gateway.hh>
#include <BusListener.hh>
#include <Babble.hh>
#include <Authenticator.hh>
#include <TokenGenerator.hh>

using namespace fys::mq;
using namespace fys::gateway;
using namespace fys::network;

using BabbleBusListener = BusListener <buslistener::Babble, FysBus<fys::pb::FySGtwMessage, BUS_QUEUES_SIZE>>;
using AuthBusListener = BusListener <buslistener::Authenticator, FysBus<fys::pb::FySGtwMessage, BUS_QUEUES_SIZE>>;

int main(int argc, const char * const *argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    try {
        boost::asio::io_service ios;
        boost::asio::io_service::work work(ios);
        Context ctx(argc, argv);
        auto fysBus = std::make_shared<FysBus<fys::pb::FySGtwMessage, BUS_QUEUES_SIZE> > (fys::pb::Type_ARRAYSIZE);
        Gateway::ptr gtw = Gateway::create(ctx, ios, fysBus);
        buslistener::Babble babble(gtw);
        buslistener::Authenticator authenticator(gtw);
        BabbleBusListener babbleListener(babble);
        AuthBusListener authenticatorListener(authenticator);

        authenticatorListener.launchListenThread(fysBus);
        babbleListener.launchListenThread(fysBus);
        std::cout << ctx << std::endl;
        std::cout << fys::utils::TokenGenerator::getInstance()->generate() << std::endl;
        gtw->runPlayerAccept();
        gtw->runServerAccept();
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
