#pragma once
#include "Sakura.h"

#ifdef SKR_PLATFORM_WINDOWS
//ȫ������
extern Sakura::Application* Sakura::createApplication();

//�����û���������
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