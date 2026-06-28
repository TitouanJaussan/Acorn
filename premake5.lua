TARGET_DIR = "bin/%{cfg.buildcfg}"

function setup_module(mod_name)
    project(mod_name)
        kind "SharedLib"
        location("build/modules/"..mod_name)
        targetdir(TARGET_DIR.."/modules")
        warnings "Extra"

        includedirs {
            "runtime/include",
            "runtime/vendor",
            "runtime/modules",
            "runtime/modules/"..mod_name
        }

        files {
            "runtime/modules/"..mod_name.."/**.cpp"
        }

        filter "system:windows"
            defines(string.upper(mod_name).."_BUILD_DLL")

        filter {}
end

function setup_all_modules()
    dirs = os.matchdirs("./runtime/modules/*")
    table.sort(dirs)

    for i = 1, #dirs do
        dirname = path.getname(dirs[i])
        setup_module(dirname)
    end
end

function setup_spdlog()
    if os.host() == "linux" then
        os.execute([[
            cd runtime/vendor/spdlog/ && mkdir -p build && cd build/ &&
            cmake .. && cmake --build .
        ]])
    
    elseif os.host() == "windows" then
        os.execute([[
            cd runtime/vendor/spdlog/ && md build/ && cd build/ &&
            cmake .. && cmake --build .
        ]])
    end
end

workspace "Acorn"
    configurations {
        "Dev",
        "Debug",
        "Release"
    }

    language "C++"
    cppdialect "C++20"
    location "build"
    architecture "x86_64"

    symbols "On"
    filter "configurations:release"
        symbols "Off"

    filter {}

project "AcornRuntime"
    kind "SharedLib"
    location "build/runtime"
    targetdir(TARGET_DIR)

    includedirs {
        "runtime/include",
        "runtime/src",
        "runtime/vendor"
    }
    
    files {
        "runtime/src/**.cpp",
    }

    setup_spdlog()

    libdirs {
        "runtime/vendor/spdlog/build"
    }

    links {
        "fmt"
    }

    filter "system:linux"
        links {
            "glfw"
        }

        visibility ("hidden")
        
    filter "system:windows"
        libdirs {
            "runtime/vendor/lib"
        }

        links {
            "glfw3"
        }
    
    filter "configurations:Dev"
        defines "ACORN_DEV"
        symbols "On"

    filter "configurations:Debug"
        defines "ACORN_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines { "ACORN_RELEASE" }
        optimize "On"

    filter "system:windows"
        defines { "ENGINE_BUILD_DLL" }

    filter {}

setup_all_modules()

project "AcornEditor"
    kind "ConsoleApp"
    location "build/editor"
    targetdir(TARGET_DIR)

    includedirs {
        "runtime/include",
        "runtime/vendor",
        "editor/src"
    }

    files {
        "editor/src/**.cpp"
    }

    links {
        "fmt",
        "AcornRuntime"
    }

project "UnitTests"
    kind "ConsoleApp"
    location "build/tests"
    targetdir "bin/unitTests"

    includedirs {
        "runtime/include",
        "tests"
    }

    files {
        "tests/**.cpp"
    }

    links {
        "fmt",
        "AcornRuntime"
    }
