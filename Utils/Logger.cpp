//
// Created by prout on 11/3/15.
//

#include <iostream>
#include <thread>
#include "Logger.hh"
#include "Helper.hh"

Logger::~Logger() { }

Logger::Logger(zmq::context_t &ctx) : logSocketWrite(ctx, ZMQ_PAIR), logSocketRead(ctx, ZMQ_PAIR)
{
    logSocketRead.bind(CONNECTION_LOGGER);
    logSocketWrite.connect(CONNECTION_LOGGER);
}


Logger          &Logger::createInstance(zmq::context_t &ctx)
{
    if (!logger)
    {
        logger = new Logger(ctx);
        std::thread loggerThread(std::bind(&Logger::run, &(*logger)));

        loggerThread.detach();
    }
    return (*logger);
}

Logger          &Logger::getInstance()
{
    if (!logger)
        std::cerr << ERROR_INSTANCE_NOT_INITIALIZED << std::endl;
    return (*logger);
}

void            Logger::deleteInstance()
{
    delete logger;
    logger = nullptr;
}

void            Logger::write(const std::string &msg, const ::Logger::Type type)
{
    std::string str = std::to_string(static_cast<int >(type)) + msg;
    zmq::message_t message;

    zmq::Helper::fillMessage(message, str);
    logSocketWrite.send(message, str.size());
}

void            Logger::run()
{
    while (true)
    {
        zmq::message_t  msg;
        logSocketRead.recv(&msg);
        std::string m(std::string(static_cast<char *>(msg.data())));
        displayLog(m);
    }
}