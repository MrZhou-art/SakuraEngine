#pragma once
#include "Sakura/core.h"

#include "Sakura/Events/Event.h"

#include "Sakura/Input/Input.h"

#include "Window.h"
#include "Sakura/Layer/LayerStack.h"
#include "Sakura/Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Sakura/Renderer/Buffer.h"
#include "Sakura/Renderer/VertexArray.h"
#include "Sakura/Renderer/RendererAPI.h"
#include "Sakura/Renderer/Shader.h"

#include "Sakura/Camera/OrthographicCamera.h"

namespace Sakura
{
	class SAKURA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();


		virtual void Render() {} // 渲染物体
		inline Window& GetWindow() const { return *m_Window; }//获取窗户

		void OnEvent(Event& e);//事件处理

		void PushLayer(Layer* layer);//压栈普通层
		void PushOverLayer(Layer* overLayer);//压栈覆盖层
	public:
		inline static Application& GetApplication() { return *s_Instance; }//获取全局唯一实例指针
	private:
		bool OnWindowClose(WindowCloseEvent& e);//窗口关闭事件

	private:
		std::unique_ptr<Window> m_Window;//应用层窗口指针

		// ------------ 图层栈 ---------------
		ImGuiLayer* m_ImGuiLayer;// ImGuiLayer 图层
		bool m_Running = true;//循环执行开关
		LayerStack m_LayerStack;//图层栈

		// ------------ 渲染器 ---------------
		std::shared_ptr<Shader>			m_Shader;
		std::shared_ptr<VertexArray>	m_VertexArray;

		std::shared_ptr<Shader>			m_SquareShader;
		std::shared_ptr<VertexArray>	m_SquareVA;
		
		//相机测试
		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;// 全局唯一实例指针
	};

	Application* createApplication();
}
