project "Glad"
    kind "StaticLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"
    
    files
    {
        "Glad/include/glad/glad.h",
        "Glad/include/KHR/khrplatform.h",
        "Glad/src/glad.c"
    }

    includedirs
    {
        "Glad/include"
    }
    
    targetdir ("../../bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("../../bin/Intermediates/" .. OutputDir .. "/%{prj.name}")
 
    filter "system:windows"
        systemversion "latest"
        defines { }
 
    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"
 
    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"
 
    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
