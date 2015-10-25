/* 
 * File:   Logs.cpp
 * Author: fys
 * 
 * Created on September 18, 2015, 4:11 PM
 */

#include <utility>
#include <iostream>
#include <thread>

#include "../../Utils/zmqHelper.hpp"
#include "Logs.hh"

Logs::~Logs()
{
}

Logs::Logs(zmq::context_t& ctx) : 
  logSockWrite(ctx, ZMQ_PUSH),
  logSockRead(ctx, ZMQ_PULL)
{
  logSockWrite.bind(INPROC_LOG);
  logSockRead.connect(INPROC_LOG);
}

void Logs::runLogThread()
{
  std::thread logThread(&Logs::waitForLog, LogSingleton);
  logThread.detach();
}

Logs *Logs::getInstance()
{
  return (LogSingleton);
}

Logs *Logs::getInstance(zmq::context_t &ctx)
{
  if (!LogSingleton)
  {
    LogSingleton = new Logs(ctx);
    Logs::runLogThread();
  }
  return (LogSingleton);
}

// Function to call

void Logs::writeLog(Logs::LogType type, const std::string& l)
{
  zmq::message_t msg;
  logSockWrite.send(zmq::fillMessage(msg, std::to_string(static_cast<int>(type)) + l));
}


// In the thread
void Logs::log(const std::string& log)
{
  if (log.size() <= 1)
    logsToWrite.push_back(std::make_pair(Logs::WARN, "Log message is empty"));
  else
  {  
    int type = static_cast<int>(log.at(0));
    logsToWrite.push_back(std::make_pair(static_cast<LogType>(type), log.substr(1)));
    if (!logsToWrite.empty())
      Logs::writtingLoop();
  }
}

void Logs::waitForLog()
{
  while (true)
  {
    zmq::message_t msg;
    logSockRead.recv(&msg);
    
    std::string stringMsg(static_cast<char*>(msg.data()));
    Logs::log(stringMsg);
    
  }
}

void Logs::writtingLoop()
{
  std::pair<LogType, std::string> log;

  while (!logsToWrite.empty())
  {
    log = logsToWrite.front();
    if (log.first == LogType::ERROR)
      std::cerr << "Log : ERROR : " << log.second << std::endl;
    else if (log.first == LogType::INFO)
      std::cerr << "Log : WARN  : " << log.second << std::endl;
    else
      std::cout << "Log : INFO  : " << log.second << std::endl;
    logsToWrite.pop_front();
  }
}
