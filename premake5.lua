INCLUDE_DIR = "include"
SOURCE_DIR = "src"
TESTS_DIR = "tests"

BUILD_DIR = "build"
LIB_DIR = "lib"
BIN_DIR = "bin"

workspace "MultiTomo"
    configurations { "Debug", "Release" }
    location "%{BUILD_DIR}"

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"
    filter {}

project "MultiTomo"
    kind "StaticLib"
    language "C++"
    cppdialect "c++20"
    targetdir "%{LIB_DIR}/%{cfg.buildcfg}"

    files {
        "%{INCLUDE_DIR}/multitomo.hpp",
        "%{SOURCE_DIR}/DetectorGeometry.cpp",
        "%{SOURCE_DIR}/DetectorPath.cpp",
        "%{SOURCE_DIR}/Utilities.cpp",
        "%{SOURCE_DIR}/VolumeGeometry.cpp",
    }

    includedirs {
        "%{INCLUDE_DIR}"
    }

project "Tests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++20"
    targetdir "%{BIN_DIR}/%{cfg.buildcfg}"

    files {
        "%{TESTS_DIR}/test_DetectorGeometry.cpp",
        "%{TESTS_DIR}/test_DetectorPath.cpp",
        "%{TESTS_DIR}/test_Utilities.cpp",
        "%{TESTS_DIR}/test_VolumeGeometry.cpp",
    }

    includedirs {
        "%{INCLUDE_DIR}"
    }
