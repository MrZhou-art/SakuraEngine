#pragma once

#include "Sakura/Events/Event.h"

#include "Window.h"
#include "Sakura/Layer/LayerStack.h"
#include "Sakura/core.h"
#include "Sakura/Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Sakura/Renderer/Buffer.h"
//��ʱ�ļ�
#include "Sakura/Renderer/Shader.h"

namespace Sakura
{
	class SAKURA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();



		inline static Application& GetApplication() { return *s_Instance; }//��ȡȫ��Ψһʵ��ָ��
		inline Window& GetWindow() const { return *m_Window; }//��ȡ����

		void OnEvent(Event& e);//�¼�����

		void PushLayer(Layer* layer);//ѹջ��ͨ��
		void PushOverLayer(Layer* overLayer);//ѹջ���ǲ�
	private:
		bool OnWindowClose(WindowCloseEvent& e);//���ڹر��¼�

		std::unique_ptr<Window> m_Window;//Ӧ�ò㴰��ָ��
		ImGuiLayer* m_ImGuiLayer;// ImGuiLayer ͼ��
		bool m_Running = true;//ѭ��ִ�п���
		LayerStack m_LayerStack;//ͼ��ջ

		// ------------ ��Ⱦ�� ---------------
		uint32_t m_VertexArray;

		std::unique_ptr<Shader>			m_Shader;
		std::unique_ptr<VertexBuffer>	m_VertexBuffer;
		std::unique_ptr<IndexBuffer>	m_IndexBuffer;
	private:
		static Application* s_Instance;//ȫ��Ψһʵ��ָ��
	};

	Application* createApplication();
}
