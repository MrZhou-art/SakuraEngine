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
		glCreateBuffers(1, &m_RendererID);							// ���� VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);				// �� VBO
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);	// �� VBO ���� GPU
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);							// ���� CPU �е� VBO
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