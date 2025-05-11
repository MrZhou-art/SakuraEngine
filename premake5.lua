-- premake5.lua

workspace "SakuraEngine"      --解决方案(.sln)
    architecture "x64"  
    platforms { "x64" }
    startproject "Sandbox"
    
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

-- 相对于解决方案的根目录 的头文件目录 的集合
IncludeDir = {}
IncludeDir["GLFW"] = "SakuraEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "SakuraEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "SakuraEngine/vendor/imgui"
IncludeDir["glm"] = "SakuraEngine/vendor/glm"

-- 引入目录中 premake5 中的 项目配置(project)
include "SakuraEngine/vendor/GLFW" 
include "SakuraEngine/vendor/Glad"
include "SakuraEngine/vendor/ImGui"

project "SakuraEngine"       -- 项目文件(.vcxproj)
    location "SakuraEngine"  -- 项目文件的输出目录
    kind "StaticLib"         -- 项目类型(库)
    language "C++"           -- 编程语言
    staticruntime "on"       -- 静态链接运行时库（如 MSVCRT)

    targetdir("bin/" .. outputdir .. "/%{prj.name}")  -- 输出目录
    objdir("bin_int/" .. outputdir .. "/%{prj.name}") -- 中间文件目录

    pchheader "sakuraPCH.h" -- 从 premake5.lua 文件当前目录寻找预编译头文件的头文件
    pchsource "SakuraEngine/src/sakuraPCH.cpp" -- 从项目根目录寻找编译头文件的源文件

    files
    {
        "%{prj.name}/src/**.h",   -- 递归包含所有 .h 文件
        "%{prj.name}/src/**.cpp", -- 递归包含所有 .cpp 文件
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs     --定义头文件路径
    {
        "%{prj.name}/vendor/spdlog/include",
        "SakuraEngine/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links -- 链接 
    {
        "GLFW", 
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"          --配置 Windows 系统
        cppdialect "C++17"           -- C++ 标准
        systemversion "latest"       -- 使用最新SDK，启用最新API

        buildoptions { "/utf-8" }    -- 启用UTF-8源代码和执行字符集

        defines     --定义预处理宏
        {
            "SKR_PLATFORM_WINDOWS",
            "SKR_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        -- 动态库需要拷贝
        -- postbuildcommands    --后处理步骤
        -- {
        --     -- 将 dll 所在目录的文件拷贝到 exe 的目录
        --     -- 使用引号分割 DLL 输出目录与拷贝目录, *** 使用 / 明确表示Sandbox为目录 ***
        --     "{COPYDIR} \"%{cfg.buildtarget.relpath}\" \"../bin/" .. outputdir .. "/Sandbox/\""
        -- }

    -- 根据配置细化设置
    -- runtime 
    --      在不同的构建模式下，程序运行时该如何连接和使用 C/C++ 运行库（CRT）,
    --      如果未来要支持 Linux/macOS，runtime 选项能自动适配，而 /MD 是 Windows 特有的参数。
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

    links   --链接
    {
        "SakuraEngine"
    }

    filter "system:windows"     
        cppdialect "C++17"       
        systemversion "latest" 
        buildoptions { "/utf-8" }  -- 启用UTF-8源代码和执行字符集
        
        defines 
        {
            "SKR_PLATFORM_WINDOWS"
        }
        
    -- 根据配置细化设置
    filter "configurations:Debug" --调试
        runtime "Debug"
        defines "SKR_DEBUG"
        symbols "on"    -- 生成调试符号

    filter "configurations:Release" --正式发行 
        runtime "Release"
        defines "SKR_RELEASE"
        optimize "On"  -- 开启优化

    filter "configurations:Dist" --最终发行
        runtime "Release"
        defines "SKR_DIST"
        optimize "On"  -- 开启优化