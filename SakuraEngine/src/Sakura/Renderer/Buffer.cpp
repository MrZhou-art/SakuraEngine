#include "sakuraPCH.h"
#include "Sakura/Renderer/Buffer.h"

#include "Sakura/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#ifdef SKR_PLATFORM_MACOS
#include "Platform/Metal/MetalBuffer.h"
#endif

#ifdef SKR_PLATFORM_LNIUX
#include "Platform/Vulkan/VulkanBuffer.h"
#endif

namespace Sakura
{
	VertexBuffer* VertexBuffer::Create(float* data,uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SAKURA_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLVertexBuffer(data, size);
		default:
			SAKURA_CORE_ASSERT(false, "Unknow RendererAPI!");
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SAKURA_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLIndexBuffer(indices, count);
		default:
			SAKURA_CORE_ASSERT(false, "Unknow RendererAPI!");
			return nullptr;
		}
	}
}