
-- premake5.lua
workspace "AuraVK-WK"
    architecture "x86_64"
    startproject "AuraVK"
    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }

project "AuraVK"
    language "C++"
    cppdialect "C++20"

    -- Generated binary files locations
    targetdir "bin/%{cfg.buildcfg}"
    objdir ("bin-int/%{cfg.buildcfg}")

    defines { "AURA_VERSION=\"1.0.0\""}

    files 
    {
        "src/core/**.h", 
        "src/core/**.hpp", 
        "src/core/**.cpp", 
        "src/render/**.h", 
        "src/render/**.hpp", 
        "src/render/**.cpp"
    }

    includedirs 
    {
        "src/core",
        "vendor/GLFW/include",
        "vendor/MoltenVK/include", 
        -- "/Users/dlaplana/VulkanSDK/1.3.275.0/macOS/include"
        os.getenv("VULKAN_SDK") .. "/include"
    }

    flags
    {
        "MultiProcessorCompile"
    }


    -- filter "system:linux"

    --     linkoptions { "-fno-pie -no-pie" }

    --     files 
    --     { 
    --     }
    --     includedirs 
    --     {
    --         "vendor/pamanager/libpamanager/src",
    --         "/usr/include/glib-2.0",
    --         "/usr/lib/x86_64-linux-gnu/glib-2.0/include",
    --         "/usr/lib/glib-2.0/include/",
    --         "/usr/lib64/glib-2.0/include/",
    --         "vendor/sdl/include"
    --     }
    --     links
    --     {
    --         "m",
    --         "dl", 
    --         "vulkan",
    --         "pthread",
    --         "X11",
    --         "Xrandr",
    --         "Xi",
    --         "pulse",
    --         "glib-2.0",
    --         "gio-2.0",
    --         "sdl_mixer",
    --         "sdl",
    --         "libvorbis",
    --         "libogg",
    --         "glfw3",
    --         "resource-system-gnu"
    --     }
    --     libdirs
    --     {
    --     }
    --     defines
    --     {
    --         "LINUX",
    --     }

    -- filter "system:windows"
    --     defines
    --     {
    --     }
    --     files 
    --     {
    --         "resources/windowsEmbeddedResources.rc",
    --     }
    --     includedirs 
    --     {
    --         "vendor/VulkanSDK/Include",
    --         "vendor/sdl/include"
    --     }
    --     links
    --     {
    --         "imagehlp", 
    --         "dinput8", 
    --         "dxguid", 
    --         "user32", 
    --         "gdi32", 
    --         "imm32", 
    --         "ole32",
    --         "oleaut32",
    --         "shell32",
    --         "version",
    --         "uuid",
    --         "Setupapi",
    --         "vulkan-1",
    --         "sdl_mixer",
    --         "sdl",
    --         "libvorbis",
    --         "libogg",
    --         "glfw3"
    --     }
    --     libdirs 
    --     {
    --         "vendor/VulkanSDK/Lib",
    --     }

    filter "system:macosx"
    
    -- Verify that VULKAN_SDK is set

    if (os.getenv("VULKAN_SDK") == nil) then
        print("VULKAN_SDK environment variable not set. Please set it to the path of the Vulkan SDK.")
        os.exit()
    end


    linkoptions { "-rpath @executable_path/../lib" } 

        libdirs
        {
            "/usr/local/lib/", 
            "vendor/MoltenVK/lib", 
            -- "vendor/Vulkan/lib"
            os.getenv("VULKAN_SDK") .. "/lib"
        }

        -- Paths for the @rpath
        runpathdirs
        {
            "/usr/local/lib/", 
            "vendor/MoltenVK/lib", 
            "vendor/Vulkan/lib"
        }

        links
        {
            "vulkan", 
            "MoltenVK",
            "glfw",
        }
        defines
        {
            "MACOSX",
        }

    filter { "configurations:Debug" }
        defines
        {
            "DEBUG",
            "PROFILING",
            "TRACY_ENABLE"
        }
        symbols "On"
        kind "ConsoleApp"


    filter { "configurations:Release" }
        defines
        {
            "NDEBUG",
            "PROFILING",
            "TRACY_ENABLE"
        }
        optimize "On"
        kind "ConsoleApp"

    filter { "configurations:Dist" }
        defines {
            "NDEBUG",
            "DISTRIBUTION_BUILD"
        }
        optimize "On"
        kind "WindowedApp"



        include "clean.lua"