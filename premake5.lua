workspace "Carbon"
    architecture "x64"
    configurations { 
        "Debug", 
        "Release", 
        "Dist" 
    }
    startproject "Sandbox"
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    -- Include directories relative to solution directory
    IncludeDir = {}
    IncludeDir["GLFW"] = "Carbon/vendors/glfw/include"
    
    -- Include premake file of submodule
    include "Carbon/vendors/glfw"
    
    -- Include Carbon project
    project "Carbon"
        location "Carbon"
        kind "SharedLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"      
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
        defines { "_CRT_SECURE_NO_WARNINGS" }
        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }
        includedirs {
            "%{prj.name}/src/",
            "%{IncludeDir.GLFW}",
        }
        links
        {
            "GLFW"
        }
        
        -- Configuration specific settings for all system
        filter "configurations:*"
            postbuildcommands {
                {"{MKDIR} ../bin/" .. outputdir .. "/Sandbox"},
                {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"}
            }
        filter "configurations:Debug"
            defines "CA_DEBUG"
            symbols "on"
            runtime "Debug"
        filter "configurations:Release"
            defines "CA_RELEASE"
            optimize "on"
            runtime "Release"
        filter "configurations:Dist"
            defines "CA_DIST"
            optimize "on"
            runtime "Release"

        -- Visual Studio IDE specific setting for Window system
        filter "system:windows"
            -- Pre Compile header detail
            pchheader "capch.h"
            pchsource "Carbon/src/capch.cpp"
            defines
            {
                "CA_PLATFORM_WINDOWS",
                "CA_BUILD_DLL",
                "GLFW_INCLUDE_NONE",
            }

        -- XCode IDE specific setting for MAC system
        filter "system:macosx"
            -- Pre Compile header detail
            pchheader "./src/capch.h"
            pchsource "./src/capch.cpp"
            defines
            {
                "CA_PLATFORM_MAC",
                "CA_BUILD_LIB",
                "GLFW_INCLUDE_NONE",
            }
    -- End Carbon project
    
    -- Include Sandbox project
    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
        includedirs {
            "Carbon/src",
            "Carbon/vendors"
        }
        links { "Carbon" }
        
        -- Configuration specific settings for all system
        filter "configurations:Debug"
            defines "CA_DEBUG"
            symbols "on"
            runtime "Debug"

        filter "configurations:Release"
            defines "CA_RELEASE"
            optimize "on"
            runtime "Release"

        filter "configurations:Dist"
            defines "CA_DIST"
            optimize "on"
            runtime "Release"

        -- Visual Studio IDE specific setting for Window system
        filter "system:windows"
            defines { "CA_PLATFORM_WINDOWS" }

        -- XCode IDE specific setting for MAC system
        filter "system:macosx"
            defines { "CA_PLATFORM_MAC" }

    -- End Sandbox project
