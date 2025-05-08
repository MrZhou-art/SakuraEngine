#pragma once

#include "Sakura/core.h"
#include <spdlog/spdlog.h>// spdlog 库
#include <spdlog/fmt/ostr.h>//输出流操作符

namespace Sakura
{
	class SAKURA_API Log
	{
	public:
		static void initLog();//初始化日志

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return mCoreLogger; }//获取开发日志记录器
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return mClientLogger; }//获取用户日志记录器

	private:
		// 记录器
		static std::shared_ptr<spdlog::logger> mCoreLogger;
		static std::shared_ptr<spdlog::logger> mClientLogger;
	};
}


//宏定义日志类型
/*
*	SAKURA_CORE_ERROR	宏名称，作为日志调用的简写。
*	(...)				可变参数列表，允许传入任意数量的参数。
*	::					全局命名空间前缀，确保找到正确的 Sakura 命名空间。(显式查找全局作用域,嵌套命名空间或同名局部实体)
*	Sakura::Log			日志系统的类或命名空间。
*	getCoreLogger()		静态方法，返回核心日志器的共享指针（通常是 spdlog::logger）。
*	->error(...)		调用日志器的 error 方法，记录错误级别的日志。
*	__VA_ARGS__			预处理器保留标识符，代表所有传入的可变参数
*/
//开发端
#define SAKURA_CORE_TRACE(...)		::Sakura::Log::getCoreLogger()->trace(__VA_ARGS__)
#define SAKURA_CORE_INFO(...)		::Sakura::Log::getCoreLogger()->info(__VA_ARGS__)
#define SAKURA_CORE_WARN(...)		::Sakura::Log::getCoreLogger()->warn(__VA_ARGS__)
#define SAKURA_CORE_ERROR(...)		::Sakura::Log::getCoreLogger()->error(__VA_ARGS__)
#define SAKURA_CORE_CRITICAL(...)	::Sakura::Log::getCoreLogger()->critical(__VA_ARGS__)
//用户端
#define SAKURA_TRACE(...)			::Sakura::Log::getClientLogger()->trace(__VA_ARGS__)
#define SAKURA_INFO(...)			::Sakura::Log::getClientLogger()->info(__VA_ARGS__)
#define SAKURA_WARN(...)			::Sakura::Log::getClientLogger()->warn(__VA_ARGS__)
#define SAKURA_ERROR(...)			::Sakura::Log::getClientLogger()->error(__VA_ARGS__)
#define SAKURA_CRITICAL(...)		::Sakura::Log::getClientLogger()->critical(__VA_ARGS__)