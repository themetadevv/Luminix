

-- Luminix OpenGL

lxgl_modules = {
    core = "../../projects/core/src",
    glad = "../../submodules/glad/include",
    glm = "../../submodules/glm",
    spdlog = "../../submodules/spdlog/include"
}

include "../../submodules/glad"

project "lxgl"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    systemversion "latest"

    targetdir ("bin/builds/%{cfg.system}/%{cfg.buildcfg}")
    objdir ("bin/intermediates/%{cfg.system}/%{cfg.buildcfg}")

    pchheader "lxglpch.h"
    pchsource "%{prj.location}/src/lxglpch.cpp"

    postbuildcommands {
        '{MKDIR} "../../exports/%{cfg.system}/%{cfg.buildcfg}"', -- create dir if its not there!
        '{COPYFILE} "%{cfg.buildtarget.abspath}" "../../exports/%{cfg.system}/%{cfg.buildcfg}/%{cfg.buildtarget.name}"',
        '{COPYFILE} "%{cfg.buildtarget.abspath}" "../../projects/sandbox/bin/builds/%{cfg.system}/%{cfg.buildcfg}/%{cfg.buildtarget.name}"'
    }

    files {
        "%{prj.location}/**.lua",
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/src",
        "%{lxgl_modules.core}", -- compile
        "%{lxgl_modules.glad}", -- compile
        "%{lxgl_modules.glm}", -- header-only
        "%{lxgl_modules.spdlog}", -- header-only
    }

    links {
        "core",
        "glad",
        "opengl32.lib"
    }

    filter "system:windows" 
        defines { "LXGL_PLATFORM_WINDOWS", "LXGL_BUILD_DLL" }   

    filter "system:linux"
        defines { "LXGL_PLATFORM_LINUX" }

    filter "system:macosx"
        defines { "LXGL_PLATFORM_MACOSX" }

    filter "configurations:Debug"
        runtime "Debug"
        optimize "Off"
        symbols "On"
        buildoptions { "/utf-8"}
        defines {
            "LXGL_DEBUG_BUILD"
        }   

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "Off"
        buildoptions { "/utf-8"}
        defines {
            "LXGL_RELEASE_BUILD"
        }   