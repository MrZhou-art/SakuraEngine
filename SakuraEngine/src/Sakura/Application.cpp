#include "sakuraPCH.h"
#include "Application.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Sakura/Renderer/RendererCommand.h"

namespace Sakura
{
	Application* Application::s_Instance = nullptr;//全局唯一实例指针
	//inline Application& Application::GetApplication() { return *s_Instance; }//获取全局唯一实例指针

	Application::Application()
	{
		// ------------ 窗口准备 --------------
		SAKURA_CORE_ASSERT(!s_Instance, "Application already exists!");
		Application::s_Instance = this;//初始化全局唯一实例指针

		m_Window = std::unique_ptr<Window>(Window::Create());//父类类型指针 Window 指针指向子类对象 WidnowsWindow
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));//初始化 m_Data 中的 eventCallback(指定事件处理函数)

		// ------------ ImGui 图层 --------------
		m_ImGuiLayer = new ImGuiLayer();
		PushOverLayer(m_ImGuiLayer);//将 ImGui 压入栈中

		// ------------ 渲染准备 --------------
		// ************** 三角形 ********************
		m_VertexArray.reset(VertexArray::Create()); // 顶点描述对象
		std::shared_ptr<VertexBuffer>	m_VertexBuffer;
		std::shared_ptr<IndexBuffer>	m_IndexBuffer;

		// 顶点信息
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
			 0.0f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices))); // 创建顶点缓冲,将顶点数据输入 GPU

		BufferLayout layout = // 顶点缓冲布局
		{
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};

		m_VertexBuffer->SetLayout(layout);				//将顶点缓冲布局设置给顶点缓冲
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);	//根据布局生成缓冲描述

		// 索引
		uint32_t indices[3] =
		{
			0, 1, 2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t))); // 创建索引缓冲,将顶点索引输入 GPU
		m_VertexArray->SetIndexBuffer(m_IndexBuffer); // 顶点缓冲布局

		// **************** Square ***************
		m_SquareVA.reset(VertexArray::Create()); // 顶点描述对象
		std::shared_ptr<VertexBuffer>	squareVB;
		std::shared_ptr<IndexBuffer>	squareIB;

		// 顶点信息
		float Squareverteices[4 * 3] =
		{
			-0.5f, -0.5f,  0.0f, 
			 0.5f, -0.5f,  0.0f, 
			 0.5f,  0.5f,  0.0f, 
			-0.5f,  0.5f,  0.0f
		};

		squareVB.reset(VertexBuffer::Create(Squareverteices, sizeof(Squareverteices))); // 创建顶点缓冲,将顶点数据输入 GPU

		BufferLayout Squarelayout = // 顶点缓冲布局
		{
			{ShaderDataType::Float3, "a_Position"}
		};

		squareVB->SetLayout(Squarelayout);				//将顶点缓冲布局设置给顶点缓冲
		m_SquareVA->AddVertexBuffer(squareVB);			//根据布局生成缓冲描述

		// 索引
		uint32_t squareIndices[2 * 3] =
		{
			0, 1, 2, 
			2, 3, 0
		};

		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))); // 创建索引缓冲,将顶点索引输入 GPU
		m_SquareVA->SetIndexBuffer(squareIB); // 顶点缓冲布局


		// ************************** Shader ************************
		std::string vertexSrc = R"(
			#version 460
			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;			

			void main()
			{
				v_Color = a_Color;
				gl_Position = vec4(a_Pos, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 460
			layout(location = 0) out vec4 color;
			
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		
		// ************* SquareShader *************
		std::string SquarevertexSrc = R"(
			#version 460
			layout(location = 0) in vec3 a_Pos;

			out vec3 v_Pos;			

			void main()
			{
				v_Pos = a_Pos;
				gl_Position = vec4(a_Pos, 1.0);
			}
		)";

		std::string SquarefragmentSrc = R"(
			#version 460
			layout(location = 0) out vec4 color;

			in vec3 v_Pos;

			void main()
			{
				color = vec4(v_Pos * 0.5 + 0.5,1.0);
			}
		)";

		m_SquareShader.reset(new Shader(SquarevertexSrc, SquarefragmentSrc));
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		printf("Welcome to Sakura engine\n");

		while (m_Running)
		{
			RendererCommand::SetClearColor({ 0.192f, 0.192f, 0.192f, 1.00f });
			RendererCommand::Clear();

			Renderer::SceneBegin();

			m_SquareShader->Bind();
			Renderer::Submit(m_SquareVA);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::SceneEnd();

			for (Layer* layer : m_LayerStack)//图层逻辑
				layer->OnUpdata();

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
			if (e.GetHandled())		// 如果在某个图层中事件处理完成,则直接跳出 for 循环
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