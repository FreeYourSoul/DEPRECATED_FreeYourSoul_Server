cmake_minimum_required(VERSION 3.3)

set(SOURCE_FILES_AUTHENTICATOR_TESTCASE
        ${SOURCE_FILES_ALL}
        ${CMAKE_SOURCE_DIR}/Server/test/mock/GatewayMock.cpp
        ${CMAKE_SOURCE_DIR}/Server/test/mock/SessionManagerMock.cpp
        AuthenticatorTestCase.cpp
        ${CMAKE_SOURCE_DIR}/Server/test/mock/MockVerifier.hpp
        ${CMAKE_SOURCE_DIR}/Server/test/mock/MockData.hpp)

# remove real class (to be replaced by mocked ones)
list(REMOVE_ITEM SOURCE_FILES_AUTHENTICATOR_TESTCASE ${CMAKE_SOURCE_DIR}/Server/src/gateway/Gateway.cpp)
list(REMOVE_ITEM SOURCE_FILES_AUTHENTICATOR_TESTCASE ${CMAKE_SOURCE_DIR}/Server/src/network/SessionManager.cpp)

message(TEST AuthenticatorTestCase.cpp COMPILED > ${SOURCE_FILES_AUTHENTICATOR_TESTCASE})

## Test executable
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

add_executable(atc ${SOURCE_FILES_AUTHENTICATOR_TESTCASE})
target_link_libraries(atc ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
set_target_properties(atc PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()
add_test(atc atc)

