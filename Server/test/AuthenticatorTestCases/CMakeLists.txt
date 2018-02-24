cmake_minimum_required(VERSION 3.3)
include(${CMAKE_SOURCE_DIR}/BoostTestHelpers.cmake)

set(SOURCE_FILES_AUTHENTICATOR_TESTCASE
        ${SOURCE_FILES_ALL}
        ${CMAKE_SOURCE_DIR}/Server/test/mock/GatewayMock.cpp
        AuthenticatorTestCase.cpp
    )
list(REMOVE_ITEM SOURCE_FILES_AUTHENTICATOR_TESTCASE ${CMAKE_SOURCE_DIR}/Server/src/gateway/Gateway.cpp)
message(TEST AuthenticatorTestCase.cpp COMPILED > ${SOURCE_FILES_AUTHENTICATOR_TESTCASE})

## Test executable
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)

add_executable(atc ${SOURCE_FILES_AUTHENTICATOR_TESTCASE})
target_link_libraries(atc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
set_target_properties(atc PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()
add_test(atc atc)

