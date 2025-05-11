#pragma once

#include "Sakura/Window.h"
#include "Sakura/Renderer/Context.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Sakura
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();

		void OnUpdata() override;

		virtual inline void* GetNativeWindow() const override { return m_Window; }//获取 GLFWwindow

		//窗口属性
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };//提供设置回调函数接口
		void SetVSync(bool enabled) override;//设置垂直同步
		bool IsVSync() const override;//判断垂直同步
	private:
		virtual void Init(const WindowProps& props);//初始化窗口
		virtual void Shutdown();//清理窗口资源，释放分配的内存，关闭窗口。
	private:
		GLFWwindow* m_Window;//声明 GLFW 窗口指针,作为 GLFW 相关函数的参数
		Context* m_Context;//声明 Context 上下文指针,调用不同的 图形 API 
 
		struct WindowData //窗口属性
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;//垂直同步
			/*
			* 开启 VSync 时，图形处理单元（GPU）会在显示器完成一次垂直回扫后，
			* 才会将新的一帧图像发送到显示器进行显示，这样可以确保屏幕上显示的图像始终是
			* 完整的、没有撕裂现象的
			*/

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;//作为窗口用户指针指向对象
	};
}