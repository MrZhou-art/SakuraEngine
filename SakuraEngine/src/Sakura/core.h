#pragma once

// 此文件定义平台信息,库和应用信息,通用头文件信息
/*
* 规范:
* 1.函数名称,类名称,结构体名,文件名使用 大驼峰命名法
* 2.类成员变量 m_Value,
	结构体成员变量使用 大驼峰命名法,
	形参使用 小驼峰命名法,
	局部成员变量使用 小驼峰命名法, 
	静态成员变量s_Value
* 3.宏 THIS_IS_A_MACRO
* 4.用于二进制判断的枚举 THIS_IS_A_ENUM
*/

//Sakura engine 支持 window x64 
#ifdef SKR_PLATFORM_WINDOWS
	#ifdef SKR_BUILD_DLL
		#define SAKURA_API _declspec(dllexport)
	#else
		#define SAKURA_API _declspec(dllimport)
	#endif 
#else
	#error Sakura engine only supports windows
#endif

//实现断言
/*
* __debugbreak() 是编译器特定的调试中断指令：
*	在 MSVC 中等同于 DebugBreak()。
*	在 GCC/Clang 中可使用 __builtin_trap()。
* 
*	   宏				描述
*	__FILE__		当前文件名（字符串）
*	__LINE__		当前行号（整数）
*	__FUNCTION__	当前函数名（字符串）
*	__TIME__		编译时间（字符串 ）
*	__DATE__		编译日期（字符串）
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

//函数适配器宏
	/* std::bind
	* 成员函数必须绑定对象：
	*	绑定成员函数时，必须提供一个对象实例（通过指针或引用），否则会导致运行时错误。
	* 参数传递方式：
	*	传递值：std::bind 默认会复制参数的值。
	*	传递引用：若需要传递引用，使用 std::ref 或 std::cref。
	*
	*  std::function 类型的参数期望的是一个可直接调用的对象，而不是原始的成员函数指针
	*  std::bind 作为适配事件系统的接口（如 std::function），确保回调能正确调用到成员函数
	*/
#define BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

//实现二进制判断
#define BIT(x) ( 1 << x ) 