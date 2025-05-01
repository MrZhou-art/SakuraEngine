#pragma once

#include "Sakura/core.h"
#include "Sakura/Events/Event.h"
#include "Sakura/Events/ApplicationEvent.h"
#include "Window.h"

namespace Sakura
{
	class SAKURA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);//事件处理

		bool WindowClose(WindowCloseEvent& e);

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* createApplication();
}
