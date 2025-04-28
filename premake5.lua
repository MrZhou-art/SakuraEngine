-- premake5.lua

workspace "SakuraEngine"      --�������(.sln)
    architecture "x64"  
    platforms { "x64" }
    
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

project "SakuraEngine"       -- ��Ŀ�ļ�(.vcxproj)
    location "SakuraEngine"  -- ��Ŀ�ļ������Ŀ¼
    kind "SharedLib"         -- ��Ŀ����(��)
    language "C++"           -- �������

    targetdir("bin/" .. outputdir .. "/%{prj.name}")  -- ���Ŀ¼
    objdir("bin_int/" .. outputdir .. "/%{prj.name}") -- �м��ļ�Ŀ¼

    files
    {
        "%{prj.name}/src/**.h",  -- �ݹ�������� .h �ļ�
        "%{prj.name}/src/**.cpp" -- �ݹ�������� .cpp �ļ�
    }

    includedirs     --����ͷ�ļ�·��
    {
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"          --���� Windows ϵͳ
        cppdialect "C++17"           -- C++ ��׼
        staticruntime "on"           -- ��̬��������ʱ�⣨�� MSVCRT��
        systemversion "latest"       -- ʹ������SDK����������API
        buildoptions { "/utf-8" }    -- ����UTF-8Դ�����ִ���ַ���
            
        defines     --����Ԥ�����
        {
            "SKR_PLATFORM_WINDOWS",
            "SKR_BUILD_DLL"
        }

        postbuildcommands    --������
        {
             --�� dll ����Ŀ¼���ļ������� exe ��Ŀ¼
            "{COPYDIR} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
        }
        
    -- ��������ϸ������
    filter "configurations:Debug" --����
        defines "SKR_DEBUG"
        symbols "on"    -- ���ɵ��Է���

    filter "configurations:Debug" --��ʽ���� 
        defines "SKR_RELEASE"
        optimize "On"  -- �����Ż�

    filter "configurations:Debug" --���շ���
        defines "SKR_DIST"
        optimize "On"  -- �����Ż�

    --filters {"system:windows", "configurations:Release"}
    --    buildoptions "/MT" --��̬������,ʹ�ö��߳�����ʱ��

project "Sandbox"
    location "SakuraEngine"  
    kind "ConsoleApp"         
    language "C++"           

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
        "SakuraEngine/src"
    }

    links   --����
    {
        "SakuraEngine"
    }

    filter "system:windows"     
        cppdialect "C++17"       
        staticruntime "on"       
        systemversion "latest"   
        buildoptions { "/utf-8" }  -- ����UTF-8Դ�����ִ���ַ���
        
        defines 
        {
            "SKR_PLATFORM_WINDOWS"
        }
        
    filter "configurations:Debug"
        defines "SKR_DEBUG"
        symbols "on"    

    filter "configurations:Debug" 
        defines "SKR_RELEASE"
        optimize "On"

    filter "configurations:Debug"
        defines "SKR_DIST"
        optimize "On"
