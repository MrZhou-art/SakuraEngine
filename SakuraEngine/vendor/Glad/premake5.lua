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

	filter "configurations:Debug" --����
        runtime "Debug" -- ʹ�ô�������Ϣ������ʱ�⣨����ϵ���ԣ���
        defines "SKR_DEBUG"
        symbols "on"    -- ���ɵ��Է���

    filter "configurations:Release" --��ʽ���� 
        runtime "Release" -- ʹ���Ż���������ʱ�⣨������ܣ�
        defines "SKR_RELEASE"
        optimize "On"  -- �����Ż�

    filter "configurations:Dist" --���շ���
        runtime "Release"
        defines "SKR_DIST"
        optimize "On"  -- �����Ż�
