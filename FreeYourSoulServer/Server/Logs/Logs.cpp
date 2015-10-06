/* 
 * File:   Logs.cpp
 * Author: fys
 * 
 * Created on September 18, 2015, 4:11 PM
 */

#include <iostream>

#include "Logs.hpp"

Logs::Logs() {
}

Logs::~Logs() {
}

void Logs::log(Logs::LogType& type, std::string& log)
{
    if (!log && log.empty())
        log(LogType::WARN, "Log string is empty or null");
    logsToWrite.push_back(std::make_pair<LogType&, std::string> (type, log));
}

void Logs::writtingLoop() 
{    
    while (true)
    {
        std::pair<LogType, std::string> log;
        
        if (!logsToWrite.empty())
        {
            log = logsToWrite.front();
            if (log && (log.first == LogType::ERROR))
                std::cerr << "Log : ERROR : " << log.second << std::endl;
            else if (log && (log.first == LogType::INFO))
                std::cerr << "Log : WARN  : " << log.second << std::endl;
            else
                std::cout << "log : " << log.second << std::endl;
        }
    }   
        
    
}
