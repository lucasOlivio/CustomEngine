project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++14"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   includedirs
   {
      "src",

	  "../Engine/src"
   }

   links
   {
      "Engine"
   }

   postbuildcommands
   {
       "{COPY} ../Engine/Extern/fmod/lib/*.dll %{cfg.buildtarget.directory}"
   }

   targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("../bin/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

       postbuildcommands
       {
           "xcopy assets\\ %{cfg.buildtarget.directory}\\assets\\ /S /E /I /Y"
       }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

       postbuildcommands
       {
           "{COPY} ../Engine/Extern/assimp/lib/Debug/*.dll %{cfg.buildtarget.directory}"
       }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

       postbuildcommands
       {
           "{COPY} ../Engine/Extern/assimp/lib/Release/*.dll %{cfg.buildtarget.directory}"
       }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"

       postbuildcommands
       {
           "{COPY} ../Engine/Extern/assimp/lib/Release/*.dll %{cfg.buildtarget.directory}"
       }
