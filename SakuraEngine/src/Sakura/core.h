#pragma once

// ���ļ�����ƽ̨��Ϣ,���Ӧ����Ϣ,ͨ��ͷ�ļ���Ϣ

//ֻ��֧�� window64 
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
