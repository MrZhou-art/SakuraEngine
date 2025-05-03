#include "sakuraPCH.h"

#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Sakura
{
	Application* Application::s_Instance = nullptr;//全局唯一实例指针
	Application& Application::GetApplication() { return *s_Instance; }//获取全局唯一实例指针
	
	Application::Application()
	{
		SAKURA_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;//初始化全局唯一实例指针

		// 错误：m_Window = std::make_unique<Window>(*(Window::Create()));
		// 通过工厂方法返回的指针创建 unique_ptr
		m_Window = std::unique_ptr<Window>(Window::Create());//父类类型指针 Window 指针指向子类对象 WidnowsWindow
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));//初始化 m_Data 中的 eventCallback(指定事件处理函数)
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		printf("Welcome to Sakura engine\n");


		while (m_Running)
		{
			m_Window->OnUpdata();//消息接受器,切换双缓存

			glClearColor(0.192f, 0.192f, 0.192f, 1.00f);//清理画面颜色
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)//图层渲染
				layer->OnUpdata();
		}
	}



	void Application::OnEvent(Event& e)//事件处理
	{
		EventDispatcher dispatcher(e);//外窗口事件分发器
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*(--it))->OnEvent(e);//执行图层中的事件
			if (e.GetHandled())//如果在某个图层中事件处理完成,则直接跳出 for 循环
				break;
		}

		SAKURA_CORE_TRACE("{0}", e.ToString());//日志报告
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();//初始化 ImGui
	}
	void Application::PushOverLayer(Layer* overLayer)
	{
		m_LayerStack.PushOverLayer(overLayer);
		overLayer->OnAttach();
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;//终止循环
		return true;
	}
}