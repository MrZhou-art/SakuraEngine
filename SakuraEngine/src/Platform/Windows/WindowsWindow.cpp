#include "sakuraPCH.h"

#include "Sakura/Log.h"
#include "WindowsWindow.h"
#include "Sakura/Events/ApplicationEvent.h"
#include "Sakura/Events/KeyEvent.h"
#include "Sakura/Events/MouseEvent.h"

namespace Sakura
{
	static bool s_GLFWInitialized = false;//��¼ glfw �Ƿ��ʼ��(�ര��ʱ�����ظ���ʼ��)

	static void GLFWErrorCallback(int error_code, const char* description)//��¼����
	{
		SAKURA_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props)//��������
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)//����
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()//����
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)//���ڳ�ʼ��
	{
		//�������Գ�ʼ��
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		SetVSync(true);

		SAKURA_CORE_INFO("Creating window {0}({1},{2})",
						m_Data.Title, m_Data.Width, m_Data.Height);

		// glfw ��ʼ��
		if (!s_GLFWInitialized)//��� GLFW δ��ʼ��
		{
			//TODO : glfwTerminate on system shutdown
			int success = glfwInit();
			SAKURA_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);//����ص�����
			s_GLFWInitialized = true;
		}

		//glfwCreateWindow
		/*
		GLFWmonitor* monitor ��
			���壺����ָ�����ڴ���ʱʹ�õ���ʾ������������ ��������� NULL�����ڽ�������ϵͳĬ����ʾ���ϣ�
				������ָ�� GLFWmonitor �ṹ�����Чָ�룬���ڻᴴ���ڶ�Ӧ����ʾ���ϡ����ڶ���ʾ�������º����ã���ָ��������ʾ���ض���ʾ����
			��;����������Ӧ�ó��򴰿ڹ̶���ʾ�ڸ������Ϳ��Ի�ȡ������ GLFWmonitor ָ�봫��˲�����
				��ȡ��ʾ�������Ϣ��ͨ�� glfwGetMonitors �Ⱥ�����
		GLFWwindow* share ��
			���壺��ʾ��ô��ڹ�����Դ����һ������ ��������� NULL�����´����Ĵ��ڲ����������ڹ�����Դ��
				��������Ч�� GLFWwindow ָ�룬�´��ڵ������ģ��� OpenGL �����Դ����������ɫ������ȣ�����ָ�����ڹ���
			��;������Ҫ������ڸ��� OpenGL ��Դ�������ظ���������ʡ��Դʱ�������ù����ڡ�
				���磬һ��Ӧ���ж����ͼ����չʾ�������ݣ��������ǹ��� OpenGL ��Դ��
		*/
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);//��������
		glfwMakeContextCurrent(m_Window);//������
		glfwSetWindowUserPointer(m_Window, &m_Data);//��������ṹ�����,ͨ���ṹ���еı������ô�������

		// GLFW �ص�����
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)//���ڳߴ���Ϣ
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent windowResize(width, height);
				data.EventCallback(windowResize);
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)//���ڹر���Ϣ
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent windowClose;
				data.EventCallback(windowClose);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)//������Ϣ
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)//���ݼ��̲�ͬ��Ϊ(����,�ɿ�,�ظ�),������ͬ��Ӧ
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent keyPress(key, 0);
						data.EventCallback(keyPress);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent keyRelease(key);
						data.EventCallback(keyRelease);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent keyPress(key, 1);// 1 �����ظ�״̬
						data.EventCallback(keyPress);
						break;
					}
				}
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)//����ƶ���Ϣ
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent mouseMove((float)xpos, (float)ypos);
				data.EventCallback(mouseMove);
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)//��갴����Ϣ
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)//������겻ͬ��Ϊ(����,�ɿ�),������ͬ��Ӧ
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent buttonPress(button);
						data.EventCallback(buttonPress);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent buttonRelease(button);
						data.EventCallback(buttonRelease);
						break;
					}
				}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)//��������Ϣ
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent mouseScroll((float)xoffset, (float)yoffset);
				data.EventCallback(mouseScroll);
			});
	}



	void WindowsWindow::Shutdown()//ִ��������
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdata()//���ڸ���
	{
		glfwPollEvents();//���¼�������ȡ���¼��������ö�Ӧ�Ļص�����(������:��������ȴ����¼������������������¼�����������)
		glfwSwapBuffers(m_Window);//����̨��������������ʾ����Ļ�ϡ�
	}

	void WindowsWindow::SetVSync(bool enabled) //���ô�ֱͬ��
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
	//��ֱͬ��
	/*
	* glfwSwapInterval(1);���ô�ֱͬ����
	* GPU ��ȴ���ʾ�����һ֡ˢ�º��ٽ���ǰ�󻺳�������������˺�ѣ����������������ӳ١�
	*/

	bool WindowsWindow::IsVSync() const //�жϴ�ֱͬ��
	{
		return m_Data.VSync;
	}
}