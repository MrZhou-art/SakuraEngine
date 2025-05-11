-- premake5.lua

workspace "SakuraEngine"      --�������(.sln)
    architecture "x64"  
    platforms { "x64" }
    startproject "Sandbox"
    
    configurations   --��������
    {
        "Debug",
        "Release",
        "Dist"
    }

--%{cfg.buildcfg}	            ��ǰ���������� Debug/Release��	"Debug"
--%{cfg.system}	                ��ǰϵͳ���� Windows/Linux��	"Windows"
--%{cfg.platform}	            ��ǰƽ̨������ x64/Win32��	    "x64"
--%{prj.name}	                ��ǰ��Ŀ��	                    "SakuraEngine"
--%{cfg.buildtarget.relpath}	����Ŀ������·��	            "bin/DebugWindowsx64/SakuraEngine/"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.platform}" --·������

-- ����ڽ�������ĸ�Ŀ¼ ��ͷ�ļ�Ŀ¼ �ļ���
IncludeDir = {}
IncludeDir["GLFW"] = "SakuraEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "SakuraEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "SakuraEngine/vendor/imgui"
IncludeDir["glm"] = "SakuraEngine/vendor/glm"

-- ����Ŀ¼�� premake5 �е� ��Ŀ����(project)
include "SakuraEngine/vendor/GLFW" 
include "SakuraEngine/vendor/Glad"
include "SakuraEngine/vendor/ImGui"

project "SakuraEngine"       -- ��Ŀ�ļ�(.vcxproj)
    location "SakuraEngine"  -- ��Ŀ�ļ������Ŀ¼
    kind "StaticLib"         -- ��Ŀ����(��)
    language "C++"           -- �������
    staticruntime "on"       -- ��̬��������ʱ�⣨�� MSVCRT)

    targetdir("bin/" .. outputdir .. "/%{prj.name}")  -- ���Ŀ¼
    objdir("bin_int/" .. outputdir .. "/%{prj.name}") -- �м��ļ�Ŀ¼

    pchheader "sakuraPCH.h" -- �� premake5.lua �ļ���ǰĿ¼Ѱ��Ԥ����ͷ�ļ���ͷ�ļ�
    pchsource "SakuraEngine/src/sakuraPCH.cpp" -- ����Ŀ��Ŀ¼Ѱ�ұ���ͷ�ļ���Դ�ļ�

    files
    {
        "%{prj.name}/src/**.h",   -- �ݹ�������� .h �ļ�
        "%{prj.name}/src/**.cpp", -- �ݹ�������� .cpp �ļ�
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs     --����ͷ�ļ�·��
    {
        "%{prj.name}/vendor/spdlog/include",
        "SakuraEngine/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links -- ���� 
    {
        "GLFW", 
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"          --���� Windows ϵͳ
        cppdialect "C++17"           -- C++ ��׼
        systemversion "latest"       -- ʹ������SDK����������API

        buildoptions { "/utf-8" }    -- ����UTF-8Դ�����ִ���ַ���

        defines     --����Ԥ�����
        {
            "SKR_PLATFORM_WINDOWS",
            "SKR_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        -- ��̬����Ҫ����
        -- postbuildcommands    --������
        -- {
        --     -- �� dll ����Ŀ¼���ļ������� exe ��Ŀ¼
        --     -- ʹ�����ŷָ� DLL ���Ŀ¼�뿽��Ŀ¼, *** ʹ�� / ��ȷ��ʾSandboxΪĿ¼ ***
        --     "{COPYDIR} \"%{cfg.buildtarget.relpath}\" \"../bin/" .. outputdir .. "/Sandbox/\""
        -- }

    -- ��������ϸ������
    -- runtime 
    --      �ڲ�ͬ�Ĺ���ģʽ�£���������ʱ��������Ӻ�ʹ�� C/C++ ���п⣨CRT��,
    --      ���δ��Ҫ֧�� Linux/macOS��runtime ѡ�����Զ����䣬�� /MD �� Windows ���еĲ�����
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



project "Sandbox"
    location "SakuraEngine"  
    kind "ConsoleApp"         
    language "C++"     
    staticruntime "on"  

    targetdir("bin/" .. outputdir .. "/%{prj.name}")  
    objdir("bin_int/" .. outputdir .. "/%{prj.name}") 

    files
    {
        "%{prj.name}/src/**.h",  
        "%{prj.name}/src/**.cpp" 
    }

    includedirs     
    {
        "SakuraEngine/vendor/spdlog/include",
        "SakuraEngine/src",
        "SakuraEngine/vendor",
        "%{IncludeDir.glm}"
    }

    links   --����
    {
        "SakuraEngine"
    }

    filter "system:windows"     
        cppdialect "C++17"       
        systemversion "latest" 
        buildoptions { "/utf-8" }  -- ����UTF-8Դ�����ִ���ַ���
        
        defines 
        {
            "SKR_PLATFORM_WINDOWS"
        }
        
    -- ��������ϸ������
    filter "configurations:Debug" --����
        runtime "Debug"
        defines "SKR_DEBUG"
        symbols "on"    -- ���ɵ��Է���

    filter "configurations:Release" --��ʽ���� 
        runtime "Release"
        defines "SKR_RELEASE"
        optimize "On"  -- �����Ż�

    filter "configurations:Dist" --���շ���
        runtime "Release"
        defines "SKR_DIST"
        optimize "On"  -- �����Ż�