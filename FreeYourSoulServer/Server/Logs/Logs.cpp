/* 
 * File:   Logs.cpp
 * Author: fys
 * 
 * Created on September 18, 2015, 4:11 PM
 */

#include <utility>
#include <iostream>

#include "Logs.hpp"

Logs::Logs()
{
}

Logs::~Logs()
{
}

void Logs::log(const Logs::LogType& type, const std::string& log)
{
  if (log.empty())
    Logs::log(LogType::WARN, "Log string is empty or null");
  logsToWrite.push_back(std::make_pair(type, log));
  if (logsToWrite.empty())
    Logs::writtingLoop();
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
      std::cout << "log : " << log.second << std::endl;
  }
}
