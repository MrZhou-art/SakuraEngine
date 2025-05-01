#include "sakuraPCH.h"

#include "Application.h"
#include "Sakura/Log.h"

#include <GLFW/glfw3.h>

namespace Sakura
{
//������������
	/* std::bind
	* ��Ա��������󶨶���
	*	�󶨳�Ա����ʱ�������ṩһ������ʵ����ͨ��ָ������ã�������ᵼ������ʱ����
	* �������ݷ�ʽ��
	*	����ֵ��std::bind Ĭ�ϻḴ�Ʋ�����ֵ��
	*	�������ã�����Ҫ�������ã�ʹ�� std::ref �� std::cref��
	* 
	*  std::function ���͵Ĳ�����������һ����ֱ�ӵ��õĶ��󣬶�����ԭʼ�ĳ�Ա����ָ��
	*  std::bind ��Ϊ�����¼�ϵͳ�Ľӿڣ��� std::function����ȷ���ص�����ȷ���õ���Ա����
	*/
#define BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

	Application::Application()
	{
		// ����m_Window = std::make_unique<Window>(*(Window::Create()));
		// ͨ�������������ص�ָ�봴�� unique_ptr
		m_Window = std::unique_ptr<Window>(Window::Create());//��������ָ�� Window ָ��ָ��������� WidnowsWindow
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));//��ʼ�� m_Data �е� eventCallback
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)//�¼�����
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
		m_Running = false;//��ֹѭ��
		return true;//�¼�
	}
}