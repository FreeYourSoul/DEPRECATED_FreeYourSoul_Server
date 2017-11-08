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

enable_testing()

add_subdirectory( Protobuff )

include_directories(
        cmake-build-debug/Protobuff
        FySMQ/include/queue
        FySMQ/include/bus
        FySMemoryManager/include
        Server/include/gateway
        Server/include/network
        Server/include/babble
        Server/include/game Utils/src)

set(SOURCE_FILES_MM)

set(SOURCE_PROTOBUF
        cmake-build-debug/Protobuff/FySBabbleMessage.pb.cc
        cmake-build-debug/Protobuff/FySGtwMessage.pb.cc
        cmake-build-debug/Protobuff/FySAuthenticationLoginMessage.pb.cc
        cmake-build-debug/Protobuff/FySAuthenticationResponse.pb.cc
)

set(SOURCE_FILES_MQ
        FySMQ/include/queue/LockFreeQueue.hh
        FySMQ/include/queue/QueueContainer.hh
        FySMQ/include/queue/LockingQueue.hh
        FySMQ/include/bus/BusListener.hh
        FySMQ/include/bus/FysBus.hh)

set(SOURCE_FILES_SRV
        Server/src/gateway/Gateway.cpp
        Server/include/gateway/Gateway.hh
        Server/src/gateway/Context.cpp
        Server/include/gateway/Context.hh
        Server/src/network/SessionManager.cpp
        Server/include/network/SessionManager.hh
        Server/src/babble/Babble.cpp
        Server/include/babble/Babble.hh
        Server/src/babble/BabbleChannel.cpp
        Server/include/babble/BabbleChannel.hh
        Server/src/network/TcpConnection.cpp
        Server/include/network/TcpConnection.hh
        Server/src/gateway/GameServerInstance.cpp
        Server/include/gateway/GameServerInstance.hh
        Server/src/gateway/Authenticator.cpp
        Server/include/gateway/Authenticator.hh
)

set(SOURCE_FILES_UTILS Utils/src/CheckVars.hh Utils/src/TokenGenerator.cpp Utils/src/TokenGenerator.hh)

set(SOURCE_FILES_ALL
        ${SOURCE_PROTOBUF}
        ${SOURCE_FILES_UTILS}
        ${SOURCE_FILES_MQ}
        ${SOURCE_FILES_MM}
        ${SOURCE_FILES_SRV})

set(SOURCE_FILES
        ${SOURCE_FILES_ALL}
        Server/src/main.cpp)

set(SOURCE_FILES_TEST
        ${SOURCE_FILES_ALL}
        FySMQ/test/TestUnitMQ.cpp
        Utils/test/TestCheckVar.cpp
        FySMQ/test/FysBusTest.hh)

### Server ###
add_executable(FreeSouls ${SOURCE_FILES})
target_link_libraries(FreeSouls proto )

# link against dynamic libraries
add_definitions(-DBOOST_ALL_DYN_LINK)

## Test executable
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(UnitTests ${SOURCE_FILES_TEST})
target_link_libraries(UnitTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(UnitTests UnitTests)