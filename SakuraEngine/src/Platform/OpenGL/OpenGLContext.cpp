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
		glfwMakeContextCurrent(m_Window);//���ɵ�ǰ���ڵ�������
		/*
		* ʹ�� glfwGetProcAddress ��ȡ��ǰ�����µ� OpenGL �����ĵ�ַ��
		* ��ͨ�� gladLoadGLLoader ����Щ����ָ����ص������У�
		* �Ӷ�ʹ�ó�����Ե��� OpenGL �ṩ�ĸ��ֺ�������ͼ����Ⱦ�Ȳ�����
		*/
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);//��ʼ�� glad
		SAKURA_CORE_ASSERT(status, "Failed to initialize Glad!");
	}
	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);//����̨��������������ʾ����Ļ�ϡ�
	}
}

