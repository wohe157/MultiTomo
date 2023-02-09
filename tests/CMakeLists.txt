project(MultiTomo_Tests)

set(INCLUDE_DIR ../include)

set(SOURCES
    test_data.cpp
    test_exceptions.cpp
    test_utilities.cpp
)

add_executable(MultiTomo_Tests ${SOURCES})
include_directories(${INCLUDE_DIR})

target_link_libraries(MultiTomo_Tests
    GTest::gtest_main
    MultiTomo_Source
)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/b796f7d44681514f58a683a3a71ff17c94edb0c1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
