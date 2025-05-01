#pragma once

#include "Sakura/Window.h"

#include <GLFW/glfw3.h>

namespace Sakura
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();

		void OnUpdata() override;

		//��������
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };//�ṩ���ûص������ӿ�
		void SetVSync(bool enabled) override;//���ô�ֱͬ��
		bool IsVSync() const override;//�жϴ�ֱͬ��
	private:
		virtual void Init(const WindowProps& props);//��ʼ������
		virtual void Shutdown();//��������Դ���ͷŷ�����ڴ棬�رմ��ڡ�
	private:
		GLFWwindow* m_Window;//���� GLFW ����ָ��,��Ϊ GLFW ��غ���������Ŀ��
 
		struct WindowData //��������
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;//��ֱͬ��
			/*
			* ���� VSync ʱ��ͼ�δ���Ԫ��GPU��������ʾ�����һ�δ�ֱ��ɨ��
			* �ŻὫ�µ�һ֡ͼ���͵���ʾ��������ʾ����������ȷ����Ļ����ʾ��ͼ��ʼ����
			* �����ġ�û��˺�������
			*/

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;//��Ϊ�����û�ָ��ָ�����
	};
}