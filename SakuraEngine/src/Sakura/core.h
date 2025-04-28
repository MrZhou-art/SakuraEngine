#pragma once

// 此文件定义平台信息,库和应用信息,通用头文件信息

//只能支持 window64 
#ifdef SKR_PLATFORM_WINDOWS
	#ifdef SKR_BUILD_DLL
		#define SAKURA_API _declspec(dllexport)
	#else
		#define SAKURA_API _declspec(dllimport)
	#endif 
#else
	#error Sakura engine only supports windows
#endif

#define BIT(x) ( 1 << x )
