
-- Luminix App Template
-- must include all submodules used by luminix

sandbox_modules = {
    core = "../../projects/core/src",
    luminix = "../../projects/luminix/src",
    lxgl = "../../projects/lxgl/src",

    glfw = "../../submodules/glfw/include",
    glad = "../../submodules/glad/include",
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

    targetdir ("bin/builds/%{cfg.system}/%{cfg.buildcfg}")
    objdir ("bin/intermediates/%{cfg.system}/%{cfg.buildcfg}")

    files {
        "%{prj.location}/**.lua",
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        -- including this project's files
        "%{prj.location}/src",

        -- including luminix framework files
        "%{sandbox_modules.core}",
        "%{sandbox_modules.luminix}",
        "%{sandbox_modules.lxgl}",

        -- include luminix's submodules
        "%{sandbox_modules.glfw}",
        "%{sandbox_modules.glad}",
        "%{sandbox_modules.glm}",
        "%{sandbox_modules.imgui}",
        "%{sandbox_modules.spdlog}",
        "%{sandbox_modules.openal_soft}",
        "%{sandbox_modules.audiofile_adamstark}",
        "%{sandbox_modules.minimp3}"
    }

    links {
        "core",
        "luminix",
        "lxgl"
    }

    postbuildcommands {
        '{MKDIR} "../../exports/%{cfg.system}/%{cfg.buildcfg}"',
        '{COPYFILE} "%{cfg.buildtarget.abspath}" "../../exports/%{cfg.system}/%{cfg.buildcfg}/%{cfg.buildtarget.name}"'
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