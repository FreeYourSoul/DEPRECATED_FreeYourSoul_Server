cmake_minimum_required(VERSION 3.3)
project(FreeSouls)

set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_timer -lboost_system -lboost_thread -Wall -Wpedantic -Wextra ")

include_directories(FySMQ/include/queue FySMQ/include/bus FySMemoryManager/include Server/include/gateway Server/include/network Server/include/babble)

set(SOURCE_FILES_MM)

set(SOURCE_FILES_MQ FySMQ/include/queue/LockFreeQueue.hh FySMQ/include/queue/QueueContainer.hh FySMQ/include/queue/LockingQueue.hh FySMQ/include/bus/IBusListener.hh)

set(SOURCE_FILES_SRV Server/src/gateway/Gateway.cpp Server/include/gateway/Gateway.hh Server/src/network/Message.cpp Server/include/network/Message.hh Server/src/game/GameBusListener.cpp Server/include/game/GameBusListener.hh Server/src/babble/BabbleBusListener.cpp Server/include/babble/BabbleBusListener.hh Server/src/gateway/AuthBusListener.cpp Server/include/gateway/AuthBusListener.hh Server/src/gateway/Context.cpp Server/include/gateway/Context.hh Server/src/network/SessionManager.cpp Server/include/network/SessionManager.hh Server/src/network/AnswerForwarder.cpp Server/include/network/AnswerForwarder.hh Server/src/babble/Babble.cpp Server/include/babble/Babble.hh Server/src/babble/BabbleChannel.cpp Server/include/babble/BabbleChannel.hh)

set(SOURCE_FILES_UTILS)

set(SOURCE_FILES_ALL ${SOURCE_FILES_MQ} ${SOURCE_FILES_MM} ${SOURCE_FILES_SRV} ${SOURCE_FILES_UTILS} Server/src/network/TcpConnection.cpp Server/include/network/TcpConnection.hh Server/src/game/FightBusListener.cpp Server/include/game/FightBusListener.hh)
set(SOURCE_FILES Server/src/main.cpp ${SOURCE_FILES_ALL} FySMQ/test/FysBusTest.hh)
set(SOURCE_FILES_TEST ${SOURCE_FILES_ALL} FySMQ/test/testUnit.cpp)

### Server ###
add_executable(FreeSouls ${SOURCE_FILES})

# link against dynamic libraries
add_definitions(-DBOOST_ALL_DYN_LINK)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

## Test executable
add_executable(UnitTests ${SOURCE_FILES_TEST})
target_link_libraries(UnitTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
