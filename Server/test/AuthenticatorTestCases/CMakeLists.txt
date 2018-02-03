cmake_minimum_required(VERSION 3.3)

include_directories(
        /cmake-build-debug/Protobuf
        /Server/include/gateway/ServerMagicExtractor.hh
        /Server/test/mock/FySMock.hpp
        /Server/test/mock/Gateway.hh
)

#set(SOURCE_FILES_MOCK_AUTHENTICATOR_TESTCASE
#        /Server/test/mock/Gateway.hh
#        /Server/test/mock/FySMock.hpp
#    )

set(SOURCE_FILES_AUTHENTICATOR_TESTCASE
        ../../src/gateway/Authenticator.cpp
        ../../src/gateway/GameServerInstance.cpp
    )

set(SOURCE_FILES_TEST_AUTHENTICATOR_TESTCASE
        ${SOURCE_FILES_AUTHENTICATOR_TESTCASE}
        ${SOURCE_FILES_UTILS}
        AuthenticatorTestCase.cpp
    )

# link against dynamic libraries
add_definitions(-DBOOST_ALL_DYN_LINK)

## Test executable
enable_language(CXX)
add_library(atc ${SOURCE_FILES_TEST_AUTHENTICATOR_TESTCASE})