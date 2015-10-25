/* 
 * File:   Logs.hpp
 * Author: fys
 *
 * Created on September 18, 2015, 4:11 PM
 */

#ifndef LOGS_HPP
#define	LOGS_HPP

#include <zmq.hpp>
#include <cstdio>
#include <string>
#include <deque>

#define INPROC_LOG "inproc://logs"

class Logs 
{
public:

    enum LogType {
        ERROR,
        WARN,
        INFO
    };

public:
    static Logs *getInstance();
    static Logs *getInstance(zmq::context_t& ctx);

    void waitForLog();
    void writeLog(Logs::LogType type, const std::string& l);

private:
    ~Logs();
    Logs(zmq::context_t& ctx);

    static void runLogThread();
    void writtingLoop();
    void log(const std::string& log);
    
private:
    zmq::socket_t logSockWrite;
    zmq::socket_t logSockRead;
    std::deque<std::pair<LogType, std::string> > logsToWrite;
    
};

static Logs *LogSingleton = NULL;

#endif	/* LOGS_HPP */

