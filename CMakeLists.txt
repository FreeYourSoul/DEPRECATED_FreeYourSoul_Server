cmake_minimum_required(VERSION 3.3)

project(FreeSouls CXX)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lprotobuf -lboost_timer -lboost_system -lboost_thread")
set(CMAKE_CXX_STANDARD 17)

if ( UNIX )
    set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Wno-deprecated-declarations")
    message( STATUS Set Warnings flag : ${CMAKE_CXX_FLAGS})
endif()

add_subdirectory(Protobuf)

include_directories(
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/Protobuf
        ${CMAKE_SOURCE_DIR}/FySMQ/include/queue
        ${CMAKE_SOURCE_DIR}/FySMQ/include/bus
        ${CMAKE_SOURCE_DIR}/FySMemoryManager/include
        ${CMAKE_SOURCE_DIR}/Server/include/gateway
        ${CMAKE_SOURCE_DIR}/Server/include/network
        ${CMAKE_SOURCE_DIR}/Server/include/babble
        ${CMAKE_SOURCE_DIR}/Server/include/game Utils/src
        ${CMAKE_SOURCE_DIR}/Server/test/itClient/include
    )

set(SOURCE_FILES_MM)

set(SOURCE_PROTOBUF
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/Protobuf/FySBabbleMessage.pb.cc
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/Protobuf/FySMessage.pb.cc
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/Protobuf/FySAuthenticationLoginMessage.pb.cc
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/Protobuf/FySAuthenticationResponse.pb.cc
    )

set(SOURCE_FILES_MQ
        ${CMAKE_SOURCE_DIR}/FySMQ/include/queue/LockFreeQueue.hh
        ${CMAKE_SOURCE_DIR}/FySMQ/include/queue/QueueContainer.hh
        ${CMAKE_SOURCE_DIR}/FySMQ/include/queue/LockingQueue.hh
        ${CMAKE_SOURCE_DIR}/FySMQ/include/bus/BusListener.hh
        ${CMAKE_SOURCE_DIR}/FySMQ/include/bus/FysBus.hh
    )

set(SOURCE_FILES_SRV
        ${CMAKE_SOURCE_DIR}/Server/src/gateway/Gateway.cpp
        ${CMAKE_SOURCE_DIR}/Server/include/gateway/Gateway.hh
        ${CMAKE_SOURCE_DIR}/Server/src/gateway/Context.cpp
        ${CMAKE_SOURCE_DIR}/Server/include/gateway/Context.hh
        ${CMAKE_SOURCE_DIR}/Server/src/network/SessionManager.cpp
        ${CMAKE_SOURCE_DIR}/Server/include/network/SessionManager.hh
        ${CMAKE_SOURCE_DIR}/Server/src/babble/Babble.cpp
        ${CMAKE_SOURCE_DIR}/Server/include/babble/Babble.hh
        ${CMAKE_SOURCE_DIR}/Server/src/babble/BabbleChannel.cpp
        ${CMAKE_SOURCE_DIR}/Server/include/babble/BabbleChannel.hh
        ${CMAKE_SOURCE_DIR}/Server/src/network/TcpConnection.cpp
        ${CMAKE_SOURCE_DIR}/Server/include/network/TcpConnection.hh
        ${CMAKE_SOURCE_DIR}/Server/src/gateway/GameServerInstance.cpp
        ${CMAKE_SOURCE_DIR}/Server/include/gateway/GameServerInstance.hh
        ${CMAKE_SOURCE_DIR}/Server/src/gateway/Authenticator.cpp
        ${CMAKE_SOURCE_DIR}/Server/include/gateway/Authenticator.hh
        ${CMAKE_SOURCE_DIR}/Server/src/gateway/ServerMagicExtractor.cpp
        ${CMAKE_SOURCE_DIR}/Server/include/gateway/ServerMagicExtractor.hh
    )

set(SOURCE_FILES_UTILS
        ${CMAKE_SOURCE_DIR}/Utils/src/CheckVars.hh
        ${CMAKE_SOURCE_DIR}/Utils/src/TokenGenerator.cpp
        ${CMAKE_SOURCE_DIR}/Utils/src/TokenGenerator.hh
        ${CMAKE_SOURCE_DIR}/Utils/src/Range.hpp
    )

set(SOURCE_FILES_ALL
        ${SOURCE_PROTOBUF}
        ${SOURCE_FILES_UTILS}
        ${SOURCE_FILES_MQ}
        ${SOURCE_FILES_MM}
        ${SOURCE_FILES_SRV}
    )

set(SOURCE_FILES
        ${SOURCE_FILES_ALL}
        ${CMAKE_SOURCE_DIR}/Server/src/main.cpp
    )

set(SOURCE_FILES_TEST
        ${SOURCE_FILES_ALL}
        ${CMAKE_SOURCE_DIR}/FySMQ/test/TestUnitMQ.cpp
        ${CMAKE_SOURCE_DIR}/Utils/test/TestCheckVar.cpp
    )

## Test executable
enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/Server/test/AuthenticatorTestCases)
add_subdirectory(${CMAKE_SOURCE_DIR}/Server/test/GatewayTestCases)
add_subdirectory(${CMAKE_SOURCE_DIR}/FySMQ)

### Server ###
message("Build FreeSouls binary")
add_executable(FreeSouls ${SOURCE_FILES})
target_link_libraries(FreeSouls proto)