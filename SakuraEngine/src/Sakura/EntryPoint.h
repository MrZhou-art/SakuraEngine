#pragma once
#include "Sakura.h"

#ifdef SKR_PLATFORM_WINDOWS
//ȫ������
extern Sakura::Application* Sakura::createApplication();

//�����û���������
int main(int argc,char** argv)
{
	Sakura::Log::initLog();// ***** ��ʼ����־ *****

	auto app = Sakura::createApplication();
	app->Run();
	delete app;

	return 0;
}

#endif