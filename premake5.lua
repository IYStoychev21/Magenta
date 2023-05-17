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
      "vendor/GLFW/include",
      "vendor/glad/include",
      "Magenta/src",
      "vendor/GLEW/include"
    }

    
    libdirs
    {
      "vendor/GLFW/lib",
      "vendor/GLEW/lib"
    }
    
    links
    {
      "Magenta",
      "glfw3dll",
      "opengl32",
      "glew32"
    }
    
    postbuildcommands
    {
        ("cp ../vendor/GLFW/lib/glfw3.dll ../bin/" .. outputdir .. "/SandBox"),
        ("cp ../vendor/GLEW/lib/glew32.dll ../bin/" .. outputdir .. "/SandBox")
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
        "%{prj.name}/src/**.h"
    }
    
    includedirs
    {
      "%{prj.name}/src",
      "vendor/GLFW/include",
      "vendor/glad/include",
      "vendor/GLEW/include"
    }

    libdirs
    {
      "vendor/GLFW/lib",
      "vendor/GLEW/lib"
    }

    links
    {
      "glfw3dll",
      "opengl32",
      "glew32"
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
  