//
// Created by FyS on 26/05/17.
//

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <tclap/ValueArg.h>
#include <tclap/CmdLine.h>
#include "Context.hh"

fys::gateway::Context::Context(const fys::gateway::Context &other) :
        _port(other._port), _serverPort(other._serverPort), _asioThread(other._asioThread), _busIniFilePath(other._busIniFilePath),
        _queuesSize(other._queuesSize), _verbose(other._verbose)
{}

fys::gateway::Context::Context(fys::gateway::Context &&other) noexcept :
        _port(other._port), _serverPort(other._serverPort), _asioThread(other._asioThread),
        _busIniFilePath(std::move(other._busIniFilePath)), _queuesSize(other._queuesSize), _verbose(other._verbose)
{}

fys::gateway::Context::Context(const int ac, const char *const *av) {
    try {
        TCLAP::CmdLine cli("Gateway of Fys Server Game", ' ', "1.0");
        TCLAP::ValueArg<std::string> configPath("c", "config", "Path of config file", true, "/home/FyS/ClionProjects/FreeYourSoul_Server/Server/resource/gateway.ini", "string");
        TCLAP::ValueArg<u_short> changePort("p", "port", "Listening Port", false, 0, "integer");
        TCLAP::ValueArg<u_short> changeServerPort("s", "sport", "Listening Port for servers", false, 0, "integer");
        TCLAP::ValueArg<std::size_t> changeThread("t", "thread", "Thread Numbers for listening", false, 0, "integer");
        TCLAP::ValueArg<bool> verbose("v", "verbose", "Print logs on standard output", false, false, "boolean");

        cli.add(configPath);
        cli.add(changePort);
        cli.add(changeServerPort);
        cli.add(changeThread);
        cli.add(verbose);
        cli.parse(ac, av);
        this->initializeFromIni(configPath.getValue());
        if (changePort.getValue() > 0)
            setPort(changePort.getValue());
        if (changeServerPort.getValue() > 0)
            setServerPort(changeServerPort.getValue());
        if (changeThread.getValue() > 0)
            setAsioThread(changeThread.getValue());
        setVerbose(verbose.getValue());
    }
    catch (std::exception &e) {
        std::cerr << "Context not initialized " << e.what() << std::endl;
    }
}

void fys::gateway::Context::initializeFromIni(const std::string &iniPath) {
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(iniPath, pt);

    std::cout << "Context Initialization..." << std::endl;
    setPort(pt.get<u_short>(GTW_INI_PORT));
    setServerPort(pt.get<u_short>(GTW_INI_SERVER_PORT));
    setAsioThread(pt.get<std::size_t>(GTW_INI_ASIO_THREADS));
    setBusIniFilePath(pt.get<std::string>(GTW_INI_BUS_PATH));
    setQueuesSize(pt.get<std::size_t>(GTW_QUEUES_SIZE));
}

u_short fys::gateway::Context::getPort() const {
    return _port;
}

void fys::gateway::Context::setPort(const u_short port) {
    Context::_port = port;
}

const std::string &fys::gateway::Context::getBusIniFilePath() const {
    return _busIniFilePath;
}

void fys::gateway::Context::setBusIniFilePath(const std::string &busIniFilePath) {
    Context::_busIniFilePath = busIniFilePath;
}

size_t fys::gateway::Context::getAsioThread() const {
    return _asioThread;
}

void fys::gateway::Context::setAsioThread(const size_t asioThread) {
    Context::_asioThread = asioThread;
}

std::size_t fys::gateway::Context::getQueuesSize() const {
    return _queuesSize;
}

void fys::gateway::Context::setQueuesSize(std::size_t _queuesSize) {
    Context::_queuesSize = _queuesSize;
}

std::ostream &fys::gateway::operator<<(std::ostream &os, const fys::gateway::Context &context) {
    os << "Current Context -> _port: " << context._port  << " serverport: " << context._serverPort << " _asioThread: " << context._asioThread << " _busIniFilePath: "
       << context._busIniFilePath << " _queuesSize: " << context._queuesSize;
    return os;
}

bool fys::gateway::Context::isVerbose() const {
    return _verbose;
}

void fys::gateway::Context::setVerbose(bool _verbose) {
    Context::_verbose = _verbose;
}

u_short fys::gateway::Context::getServerPort() const {
    return _serverPort;
}

void fys::gateway::Context::setServerPort(u_short _serverPort) {
    Context::_serverPort = _serverPort;
}
