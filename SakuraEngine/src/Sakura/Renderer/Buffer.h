#pragma once

#include "Sakura/Renderer/Renderer.h"

namespace Sakura
{
	class VertexBuffer
	{
	public:
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexBuffer* Create(float* data, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}