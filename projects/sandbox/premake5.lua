
-- Luminix App Template
-- must include all submodules used by luminix

sandbox_modules = {
    luminix_src = "../../projects/luminix/src",
    luminix_libs = "../../projects/luminix/libs",
    glfw = "../../submodules/glfw/include",
    glm = "../../submodules/glm",
    imgui = "../../submodules/imgui",
    spdlog = "../../submodules/spdlog/include",
    openal_soft = "../../submodules/openal-soft/include",
    audiofile_adamstark = "../../submodules/audiofile",
    minimp3 = "../../submodules/minimp3"
}

project "sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"
    cppdialect "C++20"
    systemversion "latest"

    targetdir ("bin/builds/%{cfg.system}")
    objdir ("bin/intermediates/%{cfg.system}")

    files {
        "%{prj.location}/**.lua",
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/libs/**.h", 
        "%{prj.location}/libs/**.cpp",
    }

    includedirs {
        -- including this project's files
        "%{prj.location}/src",
        "%{prj.location}/libs",

        -- including luminix framework files
        "%{sandbox_modules.luminix_src}",
        "%{sandbox_modules.luminix_libs}",

        -- include luminix's submodules
        "%{sandbox_modules.glfw}",
        "%{sandbox_modules.glm}",
        "%{sandbox_modules.imgui}",
        "%{sandbox_modules.spdlog}",
        "%{sandbox_modules.openal_soft}",
        "%{sandbox_modules.audiofile_adamstark}",
        "%{sandbox_modules.minimp3}"
    }

    links {
        "luminix",
        "imgui"
    }

    defines {
        "GLFW_INCLUDE_NONE",
        "_CRT_SECURE_NO_WARNINGS"
    }

    postbuildcommands {
        '{MKDIR} "../../bin"',
        '{COPYFILE} "%{cfg.buildtarget.abspath}" "../../bin/%{cfg.buildtarget.name}"'
    }

    filter "system:windows" 
        defines { "LX_APP_PLATFORM_WINDOWS" }   

    filter "system:linux"
        defines { "LX_APP_PLATFORM_LINUX" }

    filter "system:macosx"
        defines { "LX_APP_PLATFORM_MACOSX" }

    filter "configurations:Debug"
        runtime "Debug"
        optimize "Off"
        symbols "On"
        buildoptions { "/utf-8"}
        defines {
            "LX_APP_DEBUG_BUILD"
        }   

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "Off"
        buildoptions { "/utf-8"}
        defines {
            "LX_APP_RELEASE_BUILD"
        }   