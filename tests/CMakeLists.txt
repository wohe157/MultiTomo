# MultiTomo
# Copyright (C) 2023  Wouter Heyvaert
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
project(MultiTomo_Tests)

set(INCLUDE_DIR ../include)

set(SOURCES
    test_algorithms.cpp
    test_data.cpp
    test_exceptions.cpp
    test_operators.cpp
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
