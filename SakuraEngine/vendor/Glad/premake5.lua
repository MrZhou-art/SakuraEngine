project "Glad"
	kind "StaticLib"
	language "C"
    cppdialect "C++17"
	staticruntime "on"
	warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug" --调试
        runtime "Debug" -- 使用带调试信息的运行时库（方便断点调试）。
        defines "SKR_DEBUG"
        symbols "on"    -- 生成调试符号

    filter "configurations:Release" --正式发行 
        runtime "Release" -- 使用优化过的运行时库（提高性能）
        defines "SKR_RELEASE"
        optimize "On"  -- 开启优化

    filter "configurations:Dist" --最终发行
        runtime "Release"
        defines "SKR_DIST"
        optimize "On"  -- 开启优化
