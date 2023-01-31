cmake_minimum_required(VERSION 3.14)
project(MultiTomo)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

set(INCLUDE_DIR include)
set(SOURCE_DIR src)
set(TESTS_DIR test)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
    ${INCLUDE_DIR}/Algorithm.hpp
    ${INCLUDE_DIR}/Data.hpp
    ${INCLUDE_DIR}/Operator.hpp
    ${SOURCE_DIR}/Algorithm.cpp
    ${SOURCE_DIR}/Data.cpp
    ${SOURCE_DIR}/Operator.cpp
)

set(TESTS
    ${TESTS_DIR}/test_hello.cpp
)

add_library(MultiTomo STATIC ${SOURCES})
add_executable(Tests ${TESTS})
include_directories(${INCLUDE_DIR})

target_link_libraries(
    Tests
    GTest::gtest_main
)

# Build settings
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

# IDE specific settings
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tests)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/b796f7d44681514f58a683a3a71ff17c94edb0c1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
