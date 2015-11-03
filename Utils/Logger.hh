//
// Created by prout on 11/3/15.
//

#ifndef FREESOULS_LOGGER_HH
#define FREESOULS_LOGGER_HH

#include <zmq.hpp>

static const std::string CONNECTION_LOGGER = "inproc://logger_connection";
static const std::string ERROR_INSTANCE_NOT_INITIALIZED = "The instance of Logger is not initialized";

struct StdLogPolicy
{
public:
    static void write(const std::string &log)
    {
        std::cout << log << std::endl;
    }
};

class Logger
{

public:
    enum Type
    {
        ERROR, WARNING, INFO
    };

public:
    static Logger &createInstance(zmq::context_t &);
    static Logger &getInstance();
    static void deleteInstance();

    void write(const std::string &, const Type = INFO);

private:
    ~Logger();

    Logger(zmq::context_t &);

    void run();

    template <class LogPolicy = StdLogPolicy>
    void        displayLog(std::string &msg) const
    {
        Type     type = static_cast<Type>(msg[0] - '0');

        msg = msg.substr(1);
        if (type == ERROR)
            msg = "Error : " + msg;
        else if (type == WARNING)
            msg = "Warning : " + msg;
        else
            msg = "Info : " + msg;
        LogPolicy::write(msg);
    }

private:
    static Logger *logger;
    zmq::socket_t logSocketWrite;
    zmq::socket_t logSocketRead;
};

Logger *Logger::logger = NULL;


#endif //FREESOULS_LOGGER_HH
