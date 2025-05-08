#include "sakuraPCH.h"
#include "Application.h"

#include "Sakura/Input/Input.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Sakura
{
	Application* Application::s_Instance = nullptr;//ȫ��Ψһʵ��ָ��
	//inline Application& Application::GetApplication() { return *s_Instance; }//��ȡȫ��Ψһʵ��ָ��
	
	Application::Application()
	{
		SAKURA_CORE_ASSERT(!s_Instance, "Application already exists!");
		Application::s_Instance = this;//��ʼ��ȫ��Ψһʵ��ָ��

		// ����m_Window = std::make_unique<Window>(*(Window::Create()));
		// ͨ�������������ص�ָ�봴�� unique_ptr
		m_Window = std::unique_ptr<Window>(Window::Create());//��������ָ�� Window ָ��ָ��������� WidnowsWindow
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));//��ʼ�� m_Data �е� eventCallback(ָ���¼�������)

		// ImGui ͼ��
		m_ImGuiLayer = new ImGuiLayer();
		PushOverLayer(m_ImGuiLayer);//�� ImGui ѹ��ջ��

		// OpenGL ׼��
		//Vao
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		//����
		float position[3 * 3] =
		{
			-0.5f, -0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			 0.0f,  0.5f,  0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(position,sizeof(position)));

		//ʹ�� vao ��¼ vbo ����
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//����
		uint32_t indices[3] =
		{
			0, 1, 2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 460
			layout(location = 0) in vec3 pos;
			
			void main()
			{
				gl_Position = vec4(pos, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 460
			layout(location = 0) out vec4 color;
			
			void main()
			{
				color = vec4(0.6, 0.5, 0.4, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		printf("Welcome to Sakura engine\n");

		while (m_Running)
		{
			glClearColor(0.192f, 0.192f, 0.192f, 1.00f);//��������ɫ
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			m_Shader->UnBind();

			for (Layer* layer : m_LayerStack)//ͼ���߼�
				layer->OnUpdata();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)//ͼ����Ⱦ
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdata();//��Ϣ������,�л�˫����
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