-- Include file that defines "clean" action for removing build files
include "clean.lua"

workspace "Aura"
	configurations { "Debug", "Release" }

    -- Compile for x64 format. For 32 bits set to x86
    architecture "x86_64"

-- Array of the include directories
IncludeDir = {}
IncludeDir["GLM"] = "vendor/glm/glm"
IncludeDir["GLFW"] = "vendor/GLFW/include"

project "AuraGL"
	kind "ConsoleApp"  
	language "C++"  
        
    includedirs {
        "src"
--             "src/debug",
--             "src/core",
--             "src/components",
--             "src/math",
--             "src/physics",
--             "src/render",
--             "src/ui"
    }
	files { 
            "src/**.h",
            "src/**.cpp"
    }
        
    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("bin/obj/%{cfg.buildcfg}")
	
    
    filter "system:macosx"

        includedirs{
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.GLM}"
        }
        links{
            "glfw",
            "OpenGL.framework"
        }
        defines { "PLATFORM_MACOS" }
    filter "system:linux"


    -- WINDOWS Expecifications
    filter "system:windows"
        includedirs{
            "vendor/GLFW/include"
        }
        libdirs{
            "vendor/GLFW/lib"
        }
        links{
            "glfw3"
            --"OpenGL.framework"
        }
        defines { "PLATFORM_WINDOWS" }


	filter { "configurations:Debug" }  
        defines { "DEBUG" }  
        symbols "On"  
	  
	filter { "configurations:Release" }  
        defines { "NDEBUG" }  
        optimize "On"