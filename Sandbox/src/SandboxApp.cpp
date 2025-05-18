#include <Sakura.h>

#include "imgui/imgui.h"

#include <glm/glm.hpp>



// ------------- 普通图层 ------------------
class ExampleLayer : public Sakura::Layer
{
public:
	ExampleLayer()
		: Layer("example"),
		m_Camera{ -1.6f, 1.6f, -0.9f, 0.9f }, // 正交相机的投影盒子长宽应和视窗长宽一致,否则相机旋转会压缩
		m_PerspectiveCamera{ 60.0f, 1.6f / 0.9f,0.1f, 5.0f },
		m_CameraPosition{ 0.0f, 0.0f, 2.0f },
		m_CameraRotation{ 0.0f }
	{
		// ------------ 渲染准备 ----------------
		// ************** 三角形 ********************
		m_VertexArray.reset(Sakura::VertexArray::Create()); // 顶点描述对象
		std::shared_ptr<Sakura::VertexBuffer>	m_VertexBuffer;
		std::shared_ptr<Sakura::IndexBuffer>	m_IndexBuffer;

		// 顶点信息
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
			 0.0f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f
		};

		m_VertexBuffer.reset(Sakura::VertexBuffer::Create(vertices, sizeof(vertices))); // 创建顶点缓冲,将顶点数据输入 GPU

		Sakura::BufferLayout layout = // 顶点缓冲布局
		{
			{Sakura::ShaderDataType::Float3, "a_Position"},
			{Sakura::ShaderDataType::Float4, "a_Color"}
		};

		m_VertexBuffer->SetLayout(layout);				//将顶点缓冲布局设置给顶点缓冲
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);	//根据布局生成缓冲描述

		// 索引
		uint32_t indices[3] =
		{
			0, 1, 2
		};

		m_IndexBuffer.reset(Sakura::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t))); // 创建索引缓冲,将顶点索引输入 GPU
		m_VertexArray->SetIndexBuffer(m_IndexBuffer); // 顶点缓冲布局

		// **************** Square ***************
		m_SquareVA.reset(Sakura::VertexArray::Create()); // 顶点描述对象
		std::shared_ptr<Sakura::VertexBuffer>	squareVB;
		std::shared_ptr<Sakura::IndexBuffer>	squareIB;

		// 顶点信息
		float Squareverteices[4 * 3] =
		{
			-0.05f, -0.05f,  0.0f,
			 0.05f, -0.05f,  0.0f,
			 0.05f,  0.05f,  0.0f,
			-0.05f,  0.05f,  0.0f
		};

		squareVB.reset(Sakura::VertexBuffer::Create(Squareverteices, sizeof(Squareverteices))); // 创建顶点缓冲,将顶点数据输入 GPU

		Sakura::BufferLayout Squarelayout = // 顶点缓冲布局
		{
			{Sakura::ShaderDataType::Float3, "a_Position"}
		};

		squareVB->SetLayout(Squarelayout);				//将顶点缓冲布局设置给顶点缓冲
		m_SquareVA->AddVertexBuffer(squareVB);			//根据布局生成缓冲描述

		// 索引
		uint32_t squareIndices[2 * 3] =
		{
			0, 1, 2,
			2, 3, 0
		};

		squareIB.reset(Sakura::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))); // 创建索引缓冲,将顶点索引输入 GPU
		m_SquareVA->SetIndexBuffer(squareIB); // 顶点缓冲布局


		// ************** Shader ****************
		std::string vertexSrc = R"(
			#version 460
			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectMartrix;
			uniform mat4 u_Transform;
			
			out vec4 v_Color;			

			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjectMartrix * u_Transform * vec4(a_Pos, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 460
			layout(location = 0) out vec4 color;
			
			uniform vec4 u_Color;
			
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Sakura::Shader(vertexSrc, fragmentSrc));

		// ************* SquareShader *************
		std::string SquarevertexSrc = R"(
			#version 460
			layout(location = 0) in vec3 a_Pos;

			uniform mat4 u_ViewProjectMartrix;
			uniform mat4 u_Transform;

			out vec3 v_Pos;			

			void main()
			{
				v_Pos = a_Pos;
				gl_Position = u_ViewProjectMartrix * u_Transform * vec4(a_Pos, 1.0);
			}
		)";

		std::string SquarefragmentSrc = R"(
			#version 460
			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			in vec3 v_Pos;

			void main()
			{
				color = u_Color;
			}
		)";

		m_SquareShader.reset(new Sakura::Shader(SquarevertexSrc, SquarefragmentSrc));
	}

	void OnUpdata(Sakura::Timestep ts) override
	{
		// ************** 输入 *****************
		if (Sakura::Input::IsKeyPressed(SAKURA_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Sakura::Input::IsKeyPressed(SAKURA_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Sakura::Input::IsKeyPressed(SAKURA_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (Sakura::Input::IsKeyPressed(SAKURA_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Sakura::Input::IsKeyPressed(SAKURA_KEY_R))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		else if (Sakura::Input::IsKeyPressed(SAKURA_KEY_T))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		/*m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);*/
		m_PerspectiveCamera.SetPosition(m_CameraPosition);
		m_PerspectiveCamera.SetRotation(glm::vec3(0.0f, 0.0f, 1.0f), m_CameraRotation);

		// ************** 渲染 *****************
		Sakura::RendererCommand::SetClearColor({ 0.192f, 0.192f, 0.192f, 1.00f });
		Sakura::RendererCommand::Clear();

		//Sakura::Renderer::SceneBegin(m_Camera);
		Sakura::Renderer::SceneBegin(m_PerspectiveCamera);

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.3f, 0.2f, 0.8f, 1.0f);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 position = glm::vec3(x * 0.11f, y * 0.11f, 0.0f);
				glm::vec3 sacle = glm::vec3(1.0f);
				glm::mat4 Transform = glm::translate(glm::mat4(1.0f), position * sacle);
				
				if (x % 2 == 0)
					m_SquareShader->UploadUniform_Float4(redColor, "u_Color");
				else
					m_SquareShader->UploadUniform_Float4(blueColor, "u_Color");

				Sakura::Renderer::Submit(m_SquareVA, m_SquareShader, Transform);
			}
		}

		Sakura::Renderer::Submit(m_VertexArray, m_Shader);

		Sakura::Renderer::SceneEnd();
	}
	void OnEvent(Sakura::Event& e) override
	{
		Sakura::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Sakura::KeyPressedEvent>(
			BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Sakura::KeyPressedEvent event)
	{
		return false;
	}
	
	virtual void OnImGuiRender() override
	{
	}

private:
	// ************** 渲染器 *****************
	std::shared_ptr<Sakura::Shader>			m_Shader;
	std::shared_ptr<Sakura::VertexArray>	m_VertexArray;

	std::shared_ptr<Sakura::Shader>			m_SquareShader;
	std::shared_ptr<Sakura::VertexArray>	m_SquareVA;

	// ************** 相机 *****************
	Sakura::OrthographicCamera m_Camera;
	Sakura::PerspectiveCamera m_PerspectiveCamera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation;
	float m_CameraRotationSpeed = 90.0f;

	// ************** 变换 *****************
};



// --------------- 应用层 ------------------
class Sandbox : public Sakura::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}

};




// -------------- 创建应用层 -----------------
Sakura::Application* Sakura::createApplication()
{
	return new Sandbox();
}