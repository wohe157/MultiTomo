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
            "%{SourceDirs.Tests}/test_DetectorGeometry.cpp",
            "%{SourceDirs.Tests}/test_DetectorPath.cpp",
            "%{SourceDirs.Tests}/test_Utilities.cpp",
            "%{SourceDirs.Tests}/test_VolumeGeometry.cpp",
        }

        includedirs {
            "%{IncludeDirs.MultiTomo}",
            "%{IncludeDirs.Catch}",
        }

        links {
            "MultiTomo",
        }
