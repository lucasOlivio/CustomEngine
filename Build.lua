-- premake5.lua
workspace "CustomEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Dependencies"
   include "Tests/Extern/Build-GoogleTest.lua"
   include "Engine/Extern/Build-Glad.lua"
   include "Engine/Extern/Build-GLFW.lua"
group ""

group "Tests"
	include "Tests/TEST_Example/Build-Test.lua"
group ""

include "Engine/Build-Engine.lua"
include "App/Build-App.lua"