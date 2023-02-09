cmake_minimum_required(VERSION 3.16)
project(MultiTomo)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

set(INCLUDE_DIR include)
set(SOURCE_DIR src)
set(TESTS_DIR tests)

set(PCH ${INCLUDE_DIR}/mt/pch.hpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
    ${INCLUDE_DIR}/mt/pch.hpp
    ${INCLUDE_DIR}/mt/definitions.hpp
    ${INCLUDE_DIR}/mt/algorithms.hpp
    ${SOURCE_DIR}/algorithms.cpp
    ${INCLUDE_DIR}/mt/data.hpp
    ${SOURCE_DIR}/data.cpp
    ${INCLUDE_DIR}/mt/exceptions.hpp
    ${SOURCE_DIR}/exceptions.cpp
    ${INCLUDE_DIR}/mt/operators.hpp
    ${SOURCE_DIR}/operators.cpp
    ${INCLUDE_DIR}/mt/utilities.hpp
    ${SOURCE_DIR}/utilities.cpp
)

set(TESTS
    ${TESTS_DIR}/test_data.cpp
    ${TESTS_DIR}/test_exceptions.cpp
    ${TESTS_DIR}/test_utilities.cpp
)

add_library(MultiTomo STATIC ${SOURCES})
target_precompile_headers(MultiTomo PUBLIC ${PCH})

add_executable(Tests ${TESTS})
include_directories(${INCLUDE_DIR})

target_link_libraries(Tests
    GTest::gtest_main
    MultiTomo
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
