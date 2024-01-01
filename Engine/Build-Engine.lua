project "Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++14"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   defines
   {
       "_CRT_SECURE_NO_WARNINGS",
       "GLFW_INCLUDE_NONE"
   }

   includedirs
   {
      "src",

      "Extern/Glad/include",
      "Extern/glfw/include",
      "Extern/glm/include",
      "Extern/fmod/include",
      "Extern/assimp/include",
      "Extern/Lua5.4.6/include",
      "Extern/rapidjson/include"
   }

   links
   {
      "Glad",
      "GLFW",
      -- FMOD
      "Extern/fmod/lib/fmod_vc.lib",
      "Extern/fmod/lib/fmodL_vc.lib",
      -- Lua
      "Extern/Lua5.4.6/lib/lua5.4.6-static.lib",
      "Extern/Lua5.4.6/lib/cjson.lib"
   }

   targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("../bin/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

       links
        {
            "Extern/assimp/lib/Debug/assimp-vc130-mtd.lib"
        }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

       links
        {
            "Extern/assimp/lib/Release/assimp-vc130-mt.lib"
        }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"

       links
        {
            "Extern/assimp/lib/Release/assimp-vc130-mt.lib"
        }