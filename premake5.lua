workspace "Snake3D"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags { "MultiProcessorCompile" }

	location "build"

	outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

project "Snake3D"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("build/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "snkpch.h"
	pchsource "src/snkpch.cpp"

	files 
	{ 
		"src/**.h",
		"src/**.cpp",
		
		"thirdparty/libraries/imgui/imgui.cpp",
		"thirdparty/libraries/imgui/imgui_draw.cpp",
		"thirdparty/libraries/imgui/imgui_tables.cpp",
		"thirdparty/libraries/imgui/imgui_widgets.cpp",
		"thirdparty/libraries/imgui/backends/imgui_impl_sdl3.cpp",
		"thirdparty/libraries/imgui/backends/imgui_impl_opengl3.cpp",

		"thirdparty/libraries/glad/src/glad.c"
	}
	
	includedirs
	{
		"src",

		"thirdparty/libraries/spdlog/include",
		"thirdparty/libraries/assimp/include",
		"thirdparty/libraries/FreeType/include",
		"thirdparty/libraries/glad/include",
		"thirdparty/libraries/glm",
		"thirdparty/libraries/imgui",
		"thirdparty/libraries/imgui/backends",
		"thirdparty/libraries/SDL/include",
		"thirdparty/libraries/SDL/include/SDL3"
	}

	libdirs
	{
		"thirdparty/libraries/SDL/build/Debug",
		"thirdparty/libraries/assimp/build/lib/Debug",
		"thirdparty/libraries/FreeType/build/Debug"
	}

	links 
	{
		"SDL3",
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines 
		{
			"SNAKE_PLATFORM_WINDOWS",
		}

		postbuildcommands { "{COPYFILE} %{wks.location}" .. "../thirdparty/libraries/SDL/build/Debug/SDL3.dll %{cfg.targetdir}" }

	filter "configurations:Debug"
		defines "SNAKE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SNAKE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SNAKE_DIST"
		optimize "Full"

	filter { "files:thirdparty/libraries/**.cpp or thirdparty/libraries/**.c" }
		flags { "NoPCH" }
		pchheader ""  -- Explicitly clear PCH for these files
	filter {}

	filter "action:vs*"
		toolset "v145"
	filter {}