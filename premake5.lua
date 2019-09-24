workspace "Carbon"
    architecture "x64"
    configurations { 
        "Debug", 
        "Release", 
        "Dist" 
    }
    flags
    {
        "MultiProcessorCompile"
    }
    startproject "Sandbox"
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    -- Include directories relative to solution directory
    IncludeDir = {}
    IncludeDir["GLFW"] = "Carbon/vendors/glfw/include"
    IncludeDir["GLAD"] = "Carbon/vendors/glad/include"
    IncludeDir["GLM"] = "Carbon/vendors/glm/"
    
    -- Include premake file of submodule
    include "Carbon/vendors/glfw"
    include "Carbon/vendors/glad"
    
    -- Include Carbon project
    project "Carbon"
        location "Carbon"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"      
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
        defines { "_CRT_SECURE_NO_WARNINGS" }
        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/vendor/glm/glm/**.hpp",
            "%{prj.name}/vendor/glm/glm/**.inl"
        }
        defines
        {
            "_CRT_SECURE_NO_WARNINGS"
        }
        includedirs {
            "%{prj.name}/src/",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.GLAD}",
            "%{IncludeDir.GLM}"
        }
        links
        {
            "GLFW",
            "Glad",
        }
        
        -- Configuration specific settings for all system
        filter "configurations:*"
            postbuildcommands {
                --{"{MKDIR} ../bin/" .. outputdir .. "/Sandbox"},
                --{"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"}
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
            links { "opengl32.lib" }

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
            links { "pthread" }
            linkoptions
            {
                "-framework Cocoa",
                "-framework IOKit",
                "-framework CoreFoundation",
                "-framework CoreVideo",
                "-framework OpenGL"
            }
    -- End Carbon project
    
    -- Include Sandbox project
    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
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
