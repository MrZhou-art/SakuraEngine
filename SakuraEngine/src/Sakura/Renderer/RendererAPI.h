#pragma once

#include <glm/glm.hpp>

#include "Sakura/Renderer/VertexArray.h"


namespace Sakura
{
	class VertexArray;
	

	class RendererAPI
	{
	public:
		enum class API : uint8_t
		{
			None = 0,
			OpenGL = 1,
			Vulkan = 2,
			Metal = 3
		};
	public:
		RendererAPI() {}

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

	public:
		inline static API GetRendererAPI() { return s_API; }
	private:
		static API s_API;
	};
}