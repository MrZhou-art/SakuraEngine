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
		virtual void UnBind() const override;
	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_Count;
		uint32_t m_RendererID;
	};
}