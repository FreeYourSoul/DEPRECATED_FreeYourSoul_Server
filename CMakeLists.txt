cmake_minimum_required(VERSION 3.3)
project(FreeSouls)

set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lboost_timer -lboost_system -lboost_thread -lcurl -Wall -Wpedantic -Wextra ")

include_directories(FySMQ/include/queue FySMQ/include/bus FySMemoryManager/include Server/include/gateway Server/include/network Server/include/babble Server/include/game)

set(SOURCE_FILES_MM)

set(SOURCE_FILES_MQ FySMQ/include/queue/LockFreeQueue.hh FySMQ/include/queue/QueueContainer.hh FySMQ/include/queue/LockingQueue.hh FySMQ/include/bus/BusListener.hh)

set(SOURCE_FILES_SRV Server/src/gateway/Gateway.cpp Server/include/gateway/Gateway.hh Server/src/network/Message.cpp Server/include/network/Message.hh Server/src/gateway/Context.cpp Server/include/gateway/Context.hh Server/src/network/SessionManager.cpp Server/include/network/SessionManager.hh Server/src/babble/Babble.cpp Server/include/babble/Babble.hh Server/src/babble/BabbleChannel.cpp Server/include/babble/BabbleChannel.hh Server/src/network/BabbleMessage.cpp Server/include/network/BabbleMessage.hh Server/src/network/TcpConnection.cpp Server/include/network/TcpConnection.hh Server/src/network/AuthMessage.cpp Server/include/network/AuthMessage.hh Server/src/gateway/GameServerInstance.cpp Server/include/gateway/GameServerInstance.hh Server/src/gateway/Authenticator.cpp Server/include/gateway/Authenticator.hh Server/src/network/HttpAuthClient.cpp Server/include/network/HttpAuthClient.hh)

set(SOURCE_FILES_UTILS Utils/src/CheckVars.hh Utils/src/TokenGenerator.cpp Utils/src/TokenGenerator.hh)

set(SOURCE_FILES_ALL ${SOURCE_FILES_MQ} ${SOURCE_FILES_MM} ${SOURCE_FILES_SRV} ${SOURCE_FILES_UTILS})
set(SOURCE_FILES Server/src/main.cpp ${SOURCE_FILES_ALL})
set(SOURCE_FILES_TEST ${SOURCE_FILES_ALL} FySMQ/test/TestUnitMQ.cpp Utils/test/TestCheckVar.cpp FySMQ/test/FysBusTest.hh)

### Server ###
add_executable(FreeSouls ${SOURCE_FILES})

# link against dynamic libraries
add_definitions(-DBOOST_ALL_DYN_LINK)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

## Test executable
add_executable(UnitTests ${SOURCE_FILES_TEST})
target_link_libraries(UnitTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
