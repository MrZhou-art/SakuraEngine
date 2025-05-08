#include "sakuraPCH.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Sakura
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// OpenGLVertexBuffer //////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);							// 生成 VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);				// 绑定 VBO
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);	// 将 VBO 传入 GPU
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);							// 销毁 CPU 中的 VBO
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	/// OpenGLIndexBuffer ///////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}