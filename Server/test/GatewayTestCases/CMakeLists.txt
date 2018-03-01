cmake_minimum_required(VERSION 3.3)

set(SOURCE_FILES_GATEWAY_TESTCASE
        ${SOURCE_FILES_ALL}
        ${CMAKE_SOURCE_DIR}/Server/test/mock/SessionManagerMock.cpp
        ${CMAKE_SOURCE_DIR}/Server/test/mock/MockVerifier.hpp
        ${CMAKE_SOURCE_DIR}/Server/test/mock/MockData.hpp)

set(SRC_TESTCASE_GATEWAY
        testGatewayTestCase.cpp
    )

# remove real class (to be replaced by mocked ones)
list(REMOVE_ITEM SOURCE_FILES_GATEWAY_TESTCASE ${CMAKE_SOURCE_DIR}/Server/src/network/SessionManager.cpp)

message(TEST AuthenticatorTestCase.cpp COMPILED > ${SOURCE_FILES_GATEWAY_TESTCASE})

## Test executable
add_library(gtwLib ${SRC_TESTCASE_GATEWAY})
add_executable(gtw ${SOURCE_FILES_GATEWAY_TESTCASE})
target_link_libraries(gtw gtwLib)
set_target_properties(gtw PROPERTIES LINKER_LANGUAGE CXX)

