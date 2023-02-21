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
project(MultiTomo_Source)

set(INCLUDE_DIR ../include)

set(SOURCES
    ${INCLUDE_DIR}/mt/pch.hpp
    ${INCLUDE_DIR}/mt/definitions.hpp
    ${INCLUDE_DIR}/mt/algorithms.hpp
    ${INCLUDE_DIR}/mt/data.hpp
    ${INCLUDE_DIR}/mt/exceptions.hpp
    ${INCLUDE_DIR}/mt/operators.hpp
    ${INCLUDE_DIR}/mt/utilities.hpp
    definitions.cpp
    algorithms.cpp
    data.cpp
    exceptions.cpp
    operators.cpp
    utilities.cpp
)

add_library(MultiTomo_Source STATIC ${SOURCES})
include_directories(${INCLUDE_DIR})
target_precompile_headers(MultiTomo_Source PUBLIC ${INCLUDE_DIR}/mt/pch.hpp)
