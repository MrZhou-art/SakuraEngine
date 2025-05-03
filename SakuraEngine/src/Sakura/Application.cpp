#include "sakuraPCH.h"

#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Sakura
{
	Application* Application::s_Instance = nullptr;//ȫ��Ψһʵ��ָ��
	Application& Application::GetApplication() { return *s_Instance; }//��ȡȫ��Ψһʵ��ָ��
	
	Application::Application()
	{
		SAKURA_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;//��ʼ��ȫ��Ψһʵ��ָ��

		// ����m_Window = std::make_unique<Window>(*(Window::Create()));
		// ͨ�������������ص�ָ�봴�� unique_ptr
		m_Window = std::unique_ptr<Window>(Window::Create());//��������ָ�� Window ָ��ָ��������� WidnowsWindow
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));//��ʼ�� m_Data �е� eventCallback(ָ���¼�������)
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		printf("Welcome to Sakura engine\n");


		while (m_Running)
		{
			m_Window->OnUpdata();//��Ϣ������,�л�˫����

			glClearColor(0.192f, 0.192f, 0.192f, 1.00f);//��������ɫ
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)//ͼ����Ⱦ
				layer->OnUpdata();
		}
	}



	void Application::OnEvent(Event& e)//�¼�����
	{
		EventDispatcher dispatcher(e);//�ⴰ���¼��ַ���
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*(--it))->OnEvent(e);//ִ��ͼ���е��¼�
			if (e.GetHandled())//�����ĳ��ͼ�����¼��������,��ֱ������ for ѭ��
				break;
		}

		SAKURA_CORE_TRACE("{0}", e.ToString());//��־����
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();//��ʼ�� ImGui
	}
	void Application::PushOverLayer(Layer* overLayer)
	{
		m_LayerStack.PushOverLayer(overLayer);
		overLayer->OnAttach();
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;//��ֹѭ��
		return true;
	}
}