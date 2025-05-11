#pragma once

#include "Sakura/Renderer/RendererCommand.h"
#include "Sakura/Renderer/RendererAPI.h"

namespace Sakura
{
	class Renderer
	{
	public:
		static void SceneBegin();
		static void SceneEnd();   
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetRendererAPI(); }
	};
}