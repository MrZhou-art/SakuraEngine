﻿#pragma once
#include "Sakura.h"

#ifdef SKR_PLATFORM_WINDOWS
//全局声明
extern Sakura::Application* Sakura::createApplication();

//隐藏用户的主函数
int main(int argc,char** argv)
{
	Sakura::Log::initLog();// ***** 初始化日志 *****

	auto app = Sakura::createApplication();
	app->Run();
	delete app;

	return 0;
}

#endif