#pragma once
#include "../Sakura.h"

#ifdef SKR_PLATFORM_WINDOWS
//ȫ������
extern Sakura::Application* Sakura::createApplication();

//�����û���������
int main(int argc,char** argv)
{
	auto app = Sakura::createApplication();
	app->Run();
	delete app;
}

#endif