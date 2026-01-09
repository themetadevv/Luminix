

-- Luminix OpenGL

lxgl_modules = {
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

    targetdir ("bin/builds/%{cfg.system}")
    objdir ("bin/intermediates/%{cfg.system}")

    pchheader "lxglpch.h"
    pchsource "%{prj.location}/src/lxglpch.cpp"

    defines {
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
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/src",
        "%{lxgl_modules.glad}", -- compile
        "%{lxgl_modules.glm}", -- header-only
        "%{lxgl_modules.spdlog}", -- header-only
    }

    links {
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