#include "sakuraPCH.h"
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>//日志颜色

namespace Sakura
{
	//静态成员必须在类外初始化
	std::shared_ptr<spdlog::logger> Log::mCoreLogger = nullptr;
	std::shared_ptr<spdlog::logger> Log::mClientLogger = nullptr;

	void Log::initLog()// 初始化日志
	{
		//设置日志输出格式(起始颜色范围,时间,记录器的名称,要记录的实际文本,结束颜色范围)
		spdlog::set_pattern("%^[%T] %n %v%$");

		//设置开发和用户日志记录器
		mCoreLogger = spdlog::stdout_color_mt("SAKURA");
		mCoreLogger->set_level(spdlog::level::trace);

		mClientLogger = spdlog::stdout_color_mt("CLINT");
		mClientLogger->set_level(spdlog::level::trace);
	}
}