#include "Application.h"

#include "Sakura/Events/ApplicationEvent.h"
#include "Sakura/Log.h"

namespace Sakura
{
	Application::Application()
	{

	}
	Application::~Application()
	{

	}

	
	void Application::Run()
	{
		printf("Welcome to Sakura engine\n");

		WindowResizeEvent e(1280,720);
		if (e.isInCategory(EVENTCATEGORY_APPLICATION))//传统枚举会隐式转换为常量,不能使用引用传入函数
		{
			SAKURA_TRACE(e.ToString());
		}

		while (true)
		{

		}
	}

}