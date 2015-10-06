/* 
 * File:   Logs.hpp
 * Author: fys
 *
 * Created on September 18, 2015, 4:11 PM
 */

#ifndef LOGS_HPP
#define	LOGS_HPP

#include <cstdio>
#include <list>

class Logs {

public:
    enum LogType
    {
        ERROR,
        WARN,
        INFO
    };
    
public:
    ~Logs();

    void log(Logs::LogType& type, std::string& log);
    
private:
    Logs();
    void writtingLoop();
    
    std::list<std::pair<LogType, std::string> > logsToWrite;

};

#endif	/* LOGS_HPP */

