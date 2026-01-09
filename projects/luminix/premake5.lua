

-- Luminix

luminix_modules = {
    core = "../../projects/core/src",
    glfw = "../../submodules/glfw/include",
    glad = "../../submodules/glad/include",
    glm = "../../submodules/glm",
    imgui = "../../submodules/imgui",
    spdlog = "../../submodules/spdlog/include",
    openal_soft = "../../submodules/openal-soft/include",
    audiofile_adamstark = "../../submodules/audiofile",
    minimp3 = "../../submodules/minimp3"
}

include "../../submodules/glfw"
include "../../submodules/imgui"

project "luminix"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    systemversion "latest"

    targetdir ("bin/builds/%{cfg.system}")
    objdir ("bin/intermediates/%{cfg.system}")

    pchheader "lxpch.h"
    pchsource "%{prj.location}/src/lxpch.cpp"

    defines {
        "GLFW_INCLUDE_NONE",
        "_CRT_SECURE_NO_WARNINGS"
    }

    postbuildcommands {
        '{MKDIR} "../../bin"',
        '{COPYFILE} "%{cfg.buildtarget.abspath}" "../../bin/%{cfg.buildtarget.name}"',
        '{COPYFILE} "%{cfg.buildtarget.abspath}" "../sandbox/bin/builds/windows/%{cfg.buildtarget.name}"',
    }

    files {
        "%{prj.location}/**.lua",
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/libs/**.h",
        "%{prj.location}/libs/**.cpp",
    }

    includedirs {
        "%{prj.location}/src",
        "%{prj.location}/libs",
        "%{luminix_modules.core}", -- compile
        "%{luminix_modules.glfw}", -- compile
        "%{luminix_modules.glad}", -- compile
        "%{luminix_modules.glm}", -- header-only
        "%{luminix_modules.imgui}", -- compile
        "%{luminix_modules.spdlog}", -- header-only
        "%{luminix_modules.openal_soft}", -- compile/header-only
        "%{luminix_modules.audiofile_adamstark}", -- single-header-compile
        "%{luminix_modules.minimp3}" -- single-header-compile
    }

    links {
        "core",
        "glfw",
        "imgui",
        --"lxgl",
    }

    filter "configurations:Debug"
        links {
            "../../submodules/openal-soft/binaries/openal_debug.lib"
        }

    filter "configurations:Release"
        links {
            "../../submodules/openal-soft/binaries/openal_release.lib"
        }

    filter "system:windows" 
        defines { "LX_PLATFORM_WINDOWS", "LX_BUILD_DLL" }   

    filter "system:linux"
        defines { "LX_PLATFORM_LINUX" }

    filter "system:macosx"
        defines { "LX_PLATFORM_MACOSX" }

    filter "configurations:Debug"
        runtime "Debug"
        optimize "Off"
        symbols "On"
        buildoptions { "/utf-8"}
        defines {
            "LX_DEBUG_BUILD"
        }   

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "Off"
        buildoptions { "/utf-8"}
        defines {
            "LX_RELEASE_BUILD"
        }   