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
		if (e.isInCategory(EVENTCATEGORY_APPLICATION))//��ͳö�ٻ���ʽת��Ϊ����,����ʹ�����ô��뺯��
		{
			SAKURA_TRACE(e.ToString());
		}

		while (true)
		{

		}
	}

}