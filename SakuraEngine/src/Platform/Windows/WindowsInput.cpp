#include "sakuraPCH.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

namespace Sakura
{
	Input* Input::s_Instance = new WindowsInput();//�ȱ��� .h �ļ�,�õ� WindowsInput ����

	bool WindowsInput::IsKeyPressedImpl(int keyCode)
	{
		//1.��ȡ GLFWwindow 2.ʹ�� glfw �ص����� 3.���ؽ��
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keyCode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMousePressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float,float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos,(float)yPos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = WindowsInput::GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = WindowsInput::GetMousePositionImpl();
		return y;
	}
}
