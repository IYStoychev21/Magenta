workspace "Magenta"
    configurations { 
        "Debug", 
        "Release" 
    }

    architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }
    
    includedirs
    {
      "%{prj.name}/src",
      "Magenta/src"
    }

    postbuildcommands
    {
        ("{COPY} ../vendor/GLFW/lib/glfw3.dll ../bin/" .. outputdir .. "/SandBox")
    }
    
    links
    {
      "Magenta",
      "glfw3dll",
      "opengl32"
    }

    libdirs
    {
      "vendor/GLFW/lib"
    }

    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    filter "configurations:Debug"
      defines "SB_DEBUG"
      symbols "On"
    
    filter "configurations:Release"
      defines "SB_BUILD"
      optimize "On"

project "Magenta"
    location "Magenta"
    kind "StaticLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
    }
    
    includedirs
    {
      "%{prj.name}/src",
      "vendor/GLFW/include",
      "vendor/glad/include"
    }

    libdirs
    {
      "vendor/GLFW/lib"
    }

    links
    {
      "glfw3dll",
      "opengl32"
    }
    
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    filter "configurations:Debug"
      defines "MG_DEBUG"
      symbols "On"
    
    filter "configurations:Release"
      defines "MG_BUILD"
      optimize "On"