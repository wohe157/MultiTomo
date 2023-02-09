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
    algorithms.cpp
    data.cpp
    exceptions.cpp
    operators.cpp
    utilities.cpp
)

add_library(MultiTomo_Source STATIC ${SOURCES})
include_directories(${INCLUDE_DIR})
target_precompile_headers(MultiTomo_Source PUBLIC ${INCLUDE_DIR}/mt/pch.hpp)
