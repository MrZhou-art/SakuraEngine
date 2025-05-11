#include "sakuraPCH.h"
#include "OpenGLContext.h"

#include "Sakura/Log/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Sakura
{
	OpenGLContext::OpenGLContext(GLFWwindow* window): m_Window(window)
	{
		SAKURA_ASSERT(window,"Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);//生成当前窗口的上下文
		/*
		* 使用 glfwGetProcAddress 获取当前环境下的 OpenGL 函数的地址，
		* 并通过 gladLoadGLLoader 将这些函数指针加载到程序中，
		* 从而使得程序可以调用 OpenGL 提供的各种函数进行图形渲染等操作。
		*/
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);//初始化 glad
		SAKURA_CORE_ASSERT(status, "Failed to initialize Glad!");
	}
	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);//将后台缓冲区的内容显示到屏幕上。
	}
}

