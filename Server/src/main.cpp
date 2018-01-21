#include <Gateway.hh>
#include <Babble.hh>
#include <Authenticator.hh>

int main(int argc, const char * const *argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    fys::gateway::Context ctx(argc, argv);
    fys::gateway::Gateway::start(ctx);
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
