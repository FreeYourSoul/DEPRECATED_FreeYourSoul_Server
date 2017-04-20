cmake_minimum_required(VERSION 3.3)
project(FreeSouls)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_system -lboost_date_time -lboost_thread")

set(SOURCE_FILES_MM)

set(SOURCE_FILES_MQ FySMQ/src/LockFreeQueue.cpp FySMQ/include/LockFreeQueue.hh)

set(SOURCE_FILES_SRV)

set(SOURCE_FILES_UTILS)

set(SOURCE_FILES_ALL ${SOURCE_FILES_MQ} ${SOURCE_FILES_MM} ${SOURCE_FILES_SRV} ${SOURCE_FILES_UTILS})
set(SOURCE_FILES Server/src/main.cpp ${SOURCE_FILES_ALL})
set(SOURCE_FILES_TEST ${SOURCE_FILES_ALL} FySMQ/test/testUnit.cpp)

### Server ###
add_executable(FreeSouls ${SOURCE_FILES})

# link against dynamic libraries
add_definitions(-DBOOST_ALL_DYN_LINK)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

## Test executable
add_executable(UnitTests ${SOURCE_FILES_TEST})
target_link_libraries(UnitTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
