#include "sakuraPCH.h"
#include "OpenGLVertexArray.h"

#include "Sakura/Log/Log.h"

namespace Sakura
{

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		SAKURA_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has  no layout!");

		OpenGLVertexArray::Bind();	// 绑定顶点描述对象
		vertexBuffer->Bind();		// 绑定顶点缓冲区域

		auto index = 0;								// 顶点缓冲区域的索引
		auto& layout = vertexBuffer->GetLayout();	// 获取顶点缓冲布局信息
		
		

		for (auto& buffer : layout)					// 根据布局信息描述缓冲对象
		{
			/*
			* const void* offset = static_cast<const void*>(
			*	reinterpret_cast<const char*>(0) + buffer.Offset
			*	);//安全转换
			*/
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				buffer.GetComponentCount(),
				ShaderDataTypeToGLenum(buffer.Type),
				buffer.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)buffer.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		OpenGLVertexArray::Bind();
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}
