project "GoogleTest"
   kind "StaticLib"
   language "C++"
   cppdialect "C++14"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "googletest/googletest/src/gtest-all.cc" }

   includedirs
   {
      "googletest/googletest/include",
      "googletest/googletest"
   }

   targetdir ("../../../bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("../../../bin/Intermediates/" .. OutputDir .. "/%{prj.name}")

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