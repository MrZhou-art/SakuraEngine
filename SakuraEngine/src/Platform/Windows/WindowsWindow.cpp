#include "sakuraPCH.h"
#include "WindowsWindow.h"

#include "Sakura/Log/Log.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "Sakura/Events/ApplicationEvent.h"
#include "Sakura/Events/KeyEvent.h"
#include "Sakura/Events/MouseEvent.h"

namespace Sakura
{
	static bool s_GLFWInitialized = false;//记录 glfw 是否初始化(多窗口时无需重复初始化)

	static void GLFWErrorCallback(int error_code, const char* description)//记录错误
	{
		SAKURA_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props)//创建窗口(根据不同平台使用不同窗口类)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)//构造
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()//析构
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)//窗口初始化
	{
		//窗口属性初始化
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		SetVSync(true);

		SAKURA_CORE_TRACE("Creating window {0}({1},{2})",
			m_Data.Title, m_Data.Width, m_Data.Height);

		// glfw 初始化
		if (!s_GLFWInitialized)//如果 GLFW 未初始化
		{
			//TODO : glfwTerminate on system shutdown
			int success = glfwInit();
			SAKURA_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);//错误回调函数
			s_GLFWInitialized = true;
		}

		//glfwCreateWindow
		/*
		GLFWmonitor* monitor ：
			含义：用于指定窗口创建时使用的显示器（监视器） 。如果传入 NULL，窗口将创建在系统默认显示器上；
				若传入指向 GLFWmonitor 结构体的有效指针，窗口会创建在对应的显示器上。这在多显示器环境下很有用，可指定窗口显示在特定显示器。
			用途：比如想让应用程序窗口固定显示在副屏，就可以获取副屏的 GLFWmonitor 指针传入此参数。
				获取显示器相关信息可通过 glfwGetMonitors 等函数。
		GLFWwindow* share ：
			含义：表示与该窗口共享资源的另一个窗口 。如果传入 NULL，则新创建的窗口不与其他窗口共享资源；
				若传入有效的 GLFWwindow 指针，新窗口的上下文（如 OpenGL 相关资源，像纹理、着色器程序等）会与指定窗口共享。
			用途：在需要多个窗口复用 OpenGL 资源，避免重复创建、节省资源时，可设置共享窗口。
				例如，一个应用有多个视图窗口展示相似内容，可让它们共享 OpenGL 资源。
		*/
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);//创建窗口

		//根据不同 图形 API 使用不同上下文类
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();//初始化上下文
		
		glfwSetWindowUserPointer(m_Window, &m_Data);//将窗口与结构体关联,通过结构体中的变量设置窗口属性

		// GLFW 回调函数
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)//窗口尺寸消息
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);//获取窗口自定义指针(自定义窗口数据结构体)
				data.Width = width;//将监听数据记录在数据中
				data.Height = height;
				glViewport(0, 0, width, height);

				WindowResizeEvent windowResize(width, height);//将监听数据封装成事件
				data.EventCallback(windowResize);//根据对应事件调用对应函数
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)//窗口关闭消息
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent windowClose;
				data.EventCallback(windowClose);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)//键盘消息
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)//根据键盘不同行为(按下,松开,重复),做出不同响应
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
						KeyPressedEvent keyPress(key, 1);// 1 代表重复状态
						data.EventCallback(keyPress);
						break;
					}
				}
			});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint)//获取字符
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent keyType(codepoint);
				data.EventCallback(keyType);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)//鼠标移动消息
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent mouseMove((float)xpos, (float)ypos);
				data.EventCallback(mouseMove);
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)//鼠标按键消息
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)//根据鼠标不同行为(按下,松开),做出不同响应
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
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)//鼠标滚轮消息
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent mouseScroll((float)xoffset, (float)yoffset);
				data.EventCallback(mouseScroll);
			});
	}



	void WindowsWindow::Shutdown()//执行清理窗口
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdata()//窗口更新
	{
		glfwPollEvents();//从事件队列中取出事件，并调用对应的回调函数(非阻塞:函数不会等待新事件到来，处理完现有事件就立即返回)
		m_Context->SwapBuffer();//双缓冲
	}

	void WindowsWindow::SetVSync(bool enabled) //设置垂直同步
	{
		if (enabled)
			glfwSwapInterval(3);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
	//垂直同步
	/*
	* glfwSwapInterval(1);启用垂直同步。
	* GPU 会等待显示器完成一帧刷新后再交换前后缓冲区，消除画面撕裂，但可能增加输入延迟。
	*/

	bool WindowsWindow::IsVSync() const //判断垂直同步
	{
		return m_Data.VSync;
	}
}