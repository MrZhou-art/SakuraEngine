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



		inline static Application& GetApplication();//��ȡȫ��Ψһʵ��ָ��
		inline Window& GetWindow() const { return *m_Window; }//��ȡ����

		void OnEvent(Event& e);//�¼�����

		void PushLayer(Layer* layer);//��Ϸ��
		void PushOverLayer(Layer* overLayer);//���ǲ�
	private:
		bool OnWindowClose(WindowCloseEvent& e);//���ڹر��¼�

	private:
		static Application* s_Instance;//ȫ��Ψһʵ��ָ��

		std::unique_ptr<Window> m_Window;//Ӧ�ò㴰��ָ��
		bool m_Running = true;//ѭ��ִ�п���
		LayerStack m_LayerStack;//ͼ��ջ
	};

	Application* createApplication();
}
