#pragma once

#include "Sakura/Renderer/Buffer.h"

namespace Sakura
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* data, uint32_t size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		//缓冲布局
		virtual void SetLayout(const BufferLayout& bufferLayout) override { m_BufferLayout = bufferLayout; }
		virtual const BufferLayout& GetLayout() const override { return m_BufferLayout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_BufferLayout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_Count;
		uint32_t m_RendererID;
	};
}