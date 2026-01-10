

-- Core Module

core_modules = {
    spdlog = "../../submodules/spdlog/include"
}

project "core"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    systemversion "latest"

    targetdir ("bin/builds/%{cfg.system}/%{cfg.buildcfg}")
    objdir ("bin/intermediates/%{cfg.system}/%{cfg.buildcfg}")

    pchheader "corepch.h"
    pchsource "%{prj.location}/src/corepch.cpp"

    postbuildcommands {
        '{MKDIR} "../../exports/%{cfg.system}/%{cfg.buildcfg}"',
        '{COPYFILE} "%{cfg.buildtarget.abspath}" "../../exports/%{cfg.system}/%{cfg.buildcfg}/%{cfg.buildtarget.name}"',
        '{COPYFILE} "%{cfg.buildtarget.abspath}" "../../projects/sandbox/bin/builds/%{cfg.system}/%{cfg.buildcfg}/%{cfg.buildtarget.name}"'
    }

    files {
        "%{prj.location}/**.lua",
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/core/**.h",
        "%{prj.location}/src/core/**.cpp"
    }

    includedirs {
        "%{prj.location}/src",
        "%{lxgl_modules.spdlog}", -- header-only
    }

    filter "system:windows" 
        defines { "CORE_PLATFORM_WINDOWS", "CORE_BUILD_DLL" }   

    filter "system:linux"
        defines { "CORE_PLATFORM_LINUX" }

    filter "system:macosx"
        defines { "CORE_PLATFORM_MACOSX" }

    filter "configurations:Debug"
        runtime "Debug"
        optimize "Off"
        symbols "On"
        buildoptions { "/utf-8"}
        defines {
            "CORE_DEBUG_BUILD"
        }   

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "Off"
        buildoptions { "/utf-8"}
        defines {
            "CORE_RELEASE_BUILD"
        }   