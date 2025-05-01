#pragma once

#include "sakuraPCH.h"

#include "Sakura/core.h"
#include "Sakura/Events/Event.h"

namespace Sakura
{
	struct WindowProps //��������
	{
		std::string		Title;//��������
		unsigned int	Width;//���
		unsigned int	Height;//����

		WindowProps(const std::string title = "Sakura Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title),Width(width),Height(height) {} //���캯��
	};

	//��ͬ����ϵͳ����ӿ�
	class SAKURA_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Sakura::Event&)>;//������װ��ģ��,ʵ�ֽӿ�ͳһ

		virtual ~Window() {}

		virtual void OnUpdata() = 0;
		
		//��������(����,�¼��ص�,��ֱͬ��)
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());//��̬�������ڷ���
	};
}
