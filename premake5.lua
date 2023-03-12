BuildDir = "build"

workspace "MultiTomo"
    configurations { "Debug", "Release" }
    location "%{BuildDir}"
    
    language "C++"
    cppdialect "c++20"
    
	startproject "Tests"

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"
    filter {}

    LibrariesDir                = "lib/%{cfg.buildcfg}"
    BinariesDir                 = "bin/%{cfg.buildcfg}"
    
    SourceDirs = {}
    SourceDirs["MultiTomo"]     = "src"
    SourceDirs["Tests"]         = "tests"
    
    IncludeDirs = {}
    IncludeDirs["MultiTomo"]    = "include"
    IncludeDirs["Catch"]        = "extern/catch/include"

    project "MultiTomo"
        kind "StaticLib"
        targetdir "%{LibrariesDir}"

        files {
            "%{IncludeDirs.MultiTomo}/multitomo.hpp",
            "%{SourceDirs.MultiTomo}/DetectorGeometry.cpp",
            "%{SourceDirs.MultiTomo}/DetectorPath.cpp",
            "%{SourceDirs.MultiTomo}/Utilities.cpp",
            "%{SourceDirs.MultiTomo}/VolumeGeometry.cpp",
        }

        includedirs {
            "%{IncludeDirs.MultiTomo}",
        }

    project "Tests"
        kind "ConsoleApp"
        targetdir "%{BinariesDir}"

        files {
            "%{SourceDirs.Tests}/tests.cpp",
            "%{SourceDirs.Tests}/tests_DetectorGeometry.cpp",
            "%{SourceDirs.Tests}/tests_DetectorPath.cpp",
            "%{SourceDirs.Tests}/tests_Utilities.cpp",
            "%{SourceDirs.Tests}/tests_VolumeGeometry.cpp",
        }

        includedirs {
            "%{IncludeDirs.MultiTomo}",
            "%{IncludeDirs.Catch}",
        }

        links {
            "MultiTomo",
        }
