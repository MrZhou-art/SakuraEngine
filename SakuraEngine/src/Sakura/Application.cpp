#include "sakuraPCH.h"
#include "Application.h"

#include "Sakura/Input/Input.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Sakura
{
	Application* Application::s_Instance = nullptr;//全局唯一实例指针
	//inline Application& Application::GetApplication() { return *s_Instance; }//获取全局唯一实例指针
	
	Application::Application()
	{
		SAKURA_CORE_ASSERT(!s_Instance, "Application already exists!");
		Application::s_Instance = this;//初始化全局唯一实例指针

		// 错误：m_Window = std::make_unique<Window>(*(Window::Create()));
		// 通过工厂方法返回的指针创建 unique_ptr
		m_Window = std::unique_ptr<Window>(Window::Create());//父类类型指针 Window 指针指向子类对象 WidnowsWindow
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));//初始化 m_Data 中的 eventCallback(指定事件处理函数)

		// ImGui 图层
		m_ImGuiLayer = new ImGuiLayer();
		PushOverLayer(m_ImGuiLayer);//将 ImGui 压入栈中

		// OpenGL 准备
		//Vao
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		//顶点
		float position[3 * 3] =
		{
			-0.5f, -0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			 0.0f,  0.5f,  0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(position,sizeof(position)));

		//使用 vao 记录 vbo 数据
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//索引
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
			glClearColor(0.192f, 0.192f, 0.192f, 1.00f);//清理画面颜色
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			m_Shader->UnBind();

			for (Layer* layer : m_LayerStack)//图层逻辑
				layer->OnUpdata();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)//图层渲染
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdata();//消息接受器,切换双缓存
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