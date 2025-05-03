#pragma once

#include "Sakura/Events/Event.h"

#include "Window.h"
#include "LayerStack.h"
#include "Sakura/core.h"
#include "Sakura/Events/ApplicationEvent.h"

namespace Sakura
{
	class SAKURA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();



		inline static Application& GetApplication();//获取全局唯一实例指针
		inline Window& GetWindow() const { return *m_Window; }//获取窗户

		void OnEvent(Event& e);//事件处理

		void PushLayer(Layer* layer);//游戏层
		void PushOverLayer(Layer* overLayer);//覆盖层
	private:
		bool OnWindowClose(WindowCloseEvent& e);//窗口关闭事件

	private:
		static Application* s_Instance;//全局唯一实例指针

		std::unique_ptr<Window> m_Window;//应用层窗口指针
		bool m_Running = true;//循环执行开关
		LayerStack m_LayerStack;//图层栈
	};

	Application* createApplication();
}
