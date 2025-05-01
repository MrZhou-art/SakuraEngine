#pragma once

#include "sakuraPCH.h"

#include "Sakura/core.h"
#include "Sakura/Events/Event.h"

namespace Sakura
{
	struct WindowProps //窗口属性
	{
		std::string		Title;//窗口名称
		unsigned int	Width;//宽度
		unsigned int	Height;//长度

		WindowProps(const std::string title = "Sakura Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title),Width(width),Height(height) {} //构造函数
	};

	//不同操作系统桌面接口
	class SAKURA_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Sakura::Event&)>;//函数包装器模板,实现接口统一

		virtual ~Window() {}

		virtual void OnUpdata() = 0;
		
		//窗口属性(长宽,事件回调,垂直同步)
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());//静态创建窗口方法
	};
}
