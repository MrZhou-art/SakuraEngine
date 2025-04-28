-- premake5.lua

workspace "SakuraEngine"      --解决方案(.sln)
    architecture "x64"  
    platforms { "x64" }
    
    configurations   --构建配置
    {
        "Debug",
        "Release",
        "Dist"
    }

--%{cfg.buildcfg}	            当前配置名（如 Debug/Release）	"Debug"
--%{cfg.system}	                当前系统（如 Windows/Linux）	"Windows"
--%{cfg.platform}	            当前平台名（如 x64/Win32）	    "x64"
--%{prj.name}	                当前项目名	                    "SakuraEngine"
--%{cfg.buildtarget.relpath}	构建目标的相对路径	            "bin/DebugWindowsx64/SakuraEngine/"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.platform}" --路径变量

project "SakuraEngine"       -- 项目文件(.vcxproj)
    location "SakuraEngine"  -- 项目文件的输出目录
    kind "SharedLib"         -- 项目类型(库)
    language "C++"           -- 编程语言

    targetdir("bin/" .. outputdir .. "/%{prj.name}")  -- 输出目录
    objdir("bin_int/" .. outputdir .. "/%{prj.name}") -- 中间文件目录

    files
    {
        "%{prj.name}/src/**.h",  -- 递归包含所有 .h 文件
        "%{prj.name}/src/**.cpp" -- 递归包含所有 .cpp 文件
    }

    includedirs     --定义头文件路径
    {
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"          --配置 Windows 系统
        cppdialect "C++17"           -- C++ 标准
        staticruntime "on"           -- 静态链接运行时库（如 MSVCRT）
        systemversion "latest"       -- 使用最新SDK，启用最新API
        buildoptions { "/utf-8" }    -- 启用UTF-8源代码和执行字符集
            
        defines     --定义预处理宏
        {
            "SKR_PLATFORM_WINDOWS",
            "SKR_BUILD_DLL"
        }

        postbuildcommands    --后处理步骤
        {
             --将 dll 所在目录的文件拷贝到 exe 的目录
            "{COPYDIR} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
        }
        
    -- 根据配置细化设置
    filter "configurations:Debug" --调试
        defines "SKR_DEBUG"
        symbols "on"    -- 生成调试符号

    filter "configurations:Debug" --正式发行 
        defines "SKR_RELEASE"
        optimize "On"  -- 开启优化

    filter "configurations:Debug" --最终发行
        defines "SKR_DIST"
        optimize "On"  -- 开启优化

    --filters {"system:windows", "configurations:Release"}
    --    buildoptions "/MT" --静态发布库,使用多线程运行时库

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

    links   --链接
    {
        "SakuraEngine"
    }

    filter "system:windows"     
        cppdialect "C++17"       
        staticruntime "on"       
        systemversion "latest"   
        buildoptions { "/utf-8" }  -- 启用UTF-8源代码和执行字符集
        
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
