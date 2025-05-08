#pragma once

#include "Sakura/Renderer/Context.h"

struct GLFWwindow;

namespace Sakura
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* m_Window);

		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_Window;
	};
}