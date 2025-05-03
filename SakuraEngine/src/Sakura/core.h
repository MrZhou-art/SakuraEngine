#pragma once

// ���ļ�����ƽ̨��Ϣ,���Ӧ����Ϣ,ͨ��ͷ�ļ���Ϣ
/*
* �淶:
* 1.��������,������,�ṹ����,�ļ���ʹ�� ���շ�������
* 2.���Ա���� m_Value,
	�ṹ���Ա����ʹ�� ���շ�������,
	�β�ʹ�� С�շ�������,
	�ֲ���Ա����ʹ�� С�շ�������, 
	��̬��Ա����s_Value
* 3.�� THIS_IS_A_MACRO
* 4.���ڶ������жϵ�ö�� THIS_IS_A_ENUM
*/

//Sakura engine ֧�� window x64 
#ifdef SKR_PLATFORM_WINDOWS
	#ifdef SKR_BUILD_DLL
		#define SAKURA_API _declspec(dllexport)
	#else
		#define SAKURA_API _declspec(dllimport)
	#endif 
#else
	#error Sakura engine only supports windows
#endif

//ʵ�ֶ���
/*
* __debugbreak() �Ǳ������ض��ĵ����ж�ָ�
*	�� MSVC �е�ͬ�� DebugBreak()��
*	�� GCC/Clang �п�ʹ�� __builtin_trap()��
* 
*	   ��				����
*	__FILE__		��ǰ�ļ������ַ�����
*	__LINE__		��ǰ�кţ�������
*	__FUNCTION__	��ǰ���������ַ�����
*	__TIME__		����ʱ�䣨�ַ��� ��
*	__DATE__		�������ڣ��ַ�����
*/
#ifdef SAKURA_ENABLE_ASSERTS
	#define SAKURA_CORE_ASSERT(x,...) { if(!(x)){ \
											SAKURA_CORE_ERROR("Assertion Failed at {0}:{1}: {2}", __FILE__, __LINE__, __VA_ARGS__);\
											__debugbreak(); }}
	#define SAKURA_ASSERT(x,...)	  { if(!(x)){ SAKURA_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak(); }}
#else
	#define SAKURA_CORE_ASSERT(x,...)
	#define SAKURA_ASSERT(x,...)	 
#endif

//������������
	/* std::bind
	* ��Ա��������󶨶���
	*	�󶨳�Ա����ʱ�������ṩһ������ʵ����ͨ��ָ������ã�������ᵼ������ʱ����
	* �������ݷ�ʽ��
	*	����ֵ��std::bind Ĭ�ϻḴ�Ʋ�����ֵ��
	*	�������ã�����Ҫ�������ã�ʹ�� std::ref �� std::cref��
	*
	*  std::function ���͵Ĳ�����������һ����ֱ�ӵ��õĶ��󣬶�����ԭʼ�ĳ�Ա����ָ��
	*  std::bind ��Ϊ�����¼�ϵͳ�Ľӿڣ��� std::function����ȷ���ص�����ȷ���õ���Ա����
	*/
#define BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

//ʵ�ֶ������ж�
#define BIT(x) ( 1 << x ) 