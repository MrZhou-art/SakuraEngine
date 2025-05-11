#pragma once

#include "Sakura/Renderer/Renderer.h"
#include "Sakura/Renderer/RendererAPI.h"
#include "Sakura/Renderer/VertexArray.h"

namespace Sakura
{
	class RendererCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color) 
		{ 
			s_RendererAPI->SetClearColor(color); 
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}


	private:
		static RendererAPI* s_RendererAPI;
	};
}