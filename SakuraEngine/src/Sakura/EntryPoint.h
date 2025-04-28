#pragma once
#include "Sakura.h"

#ifdef SKR_PLATFORM_WINDOWS
//全局声明
extern Sakura::Application* Sakura::createApplication();

//隐藏用户的主函数
int main(int argc,char** argv)
{

	Sakura::Log::initLog();

	SAKURA_CORE_INFO("success to initialize coreLogger!");
	SAKURA_INFO("success to initialize clientLogger!");
	SAKURA_CORE_WARN("Warning!");
	SAKURA_CORE_TRACE("This is a trace!");
	SAKURA_CORE_ERROR("Error!");
	SAKURA_CORE_CRITICAL("Critical!");

	auto app = Sakura::createApplication();
	app->Run();
	delete app;

	return 0;
}

#endif