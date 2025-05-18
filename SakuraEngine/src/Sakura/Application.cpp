#include "sakuraPCH.h"
#include "Application.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Sakura/Renderer/RendererCommand.h"

#include "GLFW/glfw3.h"

namespace Sakura
{
	Application* Application::s_Instance = nullptr;//全局唯一实例指针
	//inline Application& Application::GetApplication() { return *s_Instance; }//获取全局唯一实例指针

	Application::Application()
	{
		// ------------ 核心系统 --------------
		m_LastFrameTime = 0.0f;
		// ------------ 窗口准备 --------------
		SAKURA_CORE_ASSERT(!s_Instance, "Application already exists!");
		Application::s_Instance = this;//初始化全局唯一实例指针

		m_Window = std::unique_ptr<Window>(Window::Create());//父类类型指针 Window 指针指向子类对象 WidnowsWindow
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));//初始化 m_Data 中的 eventCallback(指定事件处理函数)
		m_Window->SetVSync(true);
		// ------------ ImGui 图层 --------------
		m_ImGuiLayer = new ImGuiLayer();
		PushOverLayer(m_ImGuiLayer);//将 ImGui 压入栈中
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		SAKURA_INFO("Welcome to Sakura engine!");

		while (m_Running)
		{
			float m_Timestep = (float)glfwGetTime();
			Timestep DeltaTime = m_Timestep - m_LastFrameTime;
			m_LastFrameTime = m_Timestep;

			for (Layer* layer : m_LayerStack)//图层逻辑
				layer->OnUpdata(DeltaTime);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)//图层渲染
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdata();//消息接受器,切换双缓存
		}
	}



	void Application::OnEvent(Event& e)	//事件处理
	{
		EventDispatcher dispatcher(e);	//外窗口事件分发器
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)// 从上下渲染图层
		{
			(*(--it))->OnEvent(e);	// 执行图层中的事件
			if (e.GetHandled())		// 如果在某个图层中事件处理完成,则直接跳出 for 循环(阻塞在某一层)
				break;
		}
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