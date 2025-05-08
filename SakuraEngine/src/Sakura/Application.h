#pragma once

#include "Sakura/Events/Event.h"

#include "Window.h"
#include "Sakura/Layer/LayerStack.h"
#include "Sakura/core.h"
#include "Sakura/Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Sakura/Renderer/Buffer.h"
//暂时文件
#include "Sakura/Renderer/Shader.h"

namespace Sakura
{
	class SAKURA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();



		inline static Application& GetApplication() { return *s_Instance; }//获取全局唯一实例指针
		inline Window& GetWindow() const { return *m_Window; }//获取窗户

		void OnEvent(Event& e);//事件处理

		void PushLayer(Layer* layer);//压栈普通层
		void PushOverLayer(Layer* overLayer);//压栈覆盖层
	private:
		bool OnWindowClose(WindowCloseEvent& e);//窗口关闭事件

		std::unique_ptr<Window> m_Window;//应用层窗口指针
		ImGuiLayer* m_ImGuiLayer;// ImGuiLayer 图层
		bool m_Running = true;//循环执行开关
		LayerStack m_LayerStack;//图层栈

		// ------------ 渲染器 ---------------
		uint32_t m_VertexArray;

		std::unique_ptr<Shader>			m_Shader;
		std::unique_ptr<VertexBuffer>	m_VertexBuffer;
		std::unique_ptr<IndexBuffer>	m_IndexBuffer;
	private:
		static Application* s_Instance;//全局唯一实例指针
	};

	Application* createApplication();
}
