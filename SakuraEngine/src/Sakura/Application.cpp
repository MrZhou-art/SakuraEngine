#include "sakuraPCH.h"

#include "Application.h"
#include "Sakura/Log.h"

#include <GLFW/glfw3.h>

namespace Sakura
{
//函数适配器宏
	/* std::bind
	* 成员函数必须绑定对象：
	*	绑定成员函数时，必须提供一个对象实例（通过指针或引用），否则会导致运行时错误。
	* 参数传递方式：
	*	传递值：std::bind 默认会复制参数的值。
	*	传递引用：若需要传递引用，使用 std::ref 或 std::cref。
	* 
	*  std::function 类型的参数期望的是一个可直接调用的对象，而不是原始的成员函数指针
	*  std::bind 作为适配事件系统的接口（如 std::function），确保回调能正确调用到成员函数
	*/
#define BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

	Application::Application()
	{
		// 错误：m_Window = std::make_unique<Window>(*(Window::Create()));
		// 通过工厂方法返回的指针创建 unique_ptr
		m_Window = std::unique_ptr<Window>(Window::Create());//父类类型指针 Window 指针指向子类对象 WidnowsWindow
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));//初始化 m_Data 中的 eventCallback
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)//事件处理
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::WindowClose));

		SAKURA_CORE_TRACE("{0}", e.ToString());
	}

	

	void Application::Run()
	{
		printf("Welcome to Sakura engine\n");

		while (m_Running)
		{
			m_Window->OnUpdata();
		}
	}

	bool Application::WindowClose(WindowCloseEvent& e)
	{
		m_Running = false;//终止循环
		return true;//事件
	}
}