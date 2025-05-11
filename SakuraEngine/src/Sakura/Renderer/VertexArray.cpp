#include "sakuraPCH.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Sakura/Renderer/Renderer.h"

namespace Sakura
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SAKURA_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLVertexArray();
		default:
			SAKURA_CORE_ASSERT(false, "Unknow RendererAPI!");
			return nullptr;
		}
	}
}
