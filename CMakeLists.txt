cmake_minimum_required(VERSION 3.3)
project(FreeSouls)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -lzmq")

set(SOURCE_FILES main.cpp Server/Actions/ActionDispatcher.cpp Server/Actions/ActionDispatcher.hh Server/ServerProxy.cpp Server/ServerProxy.hh Server/ServerRelay.cpp Server/ServerRelay.hh Utils/Logger.cpp Utils/Logger.hh Utils/Helper.cpp Utils/Helper.hh Server/Actions/ActionForwarder.cpp Server/Actions/ActionForwarder.hh Server/Actions/AnswerForwarder.cpp Server/Actions/AnswerForwarder.hh)
add_executable(FreeSouls ${SOURCE_FILES})