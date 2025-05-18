#pragma once

#include "Sakura/Renderer/RendererCommand.h"
#include "Sakura/Renderer/RendererAPI.h"
#include "Sakura/Renderer/Shader.h"

#include "Sakura/Camera/OrthographicCamera.h"
#include "Sakura/Camera/PerspectiveCamera.h"

namespace Sakura
{
	class Renderer
	{
	public:
		/*static void SceneBegin(const OrthographicCamera& camera);*/
		static void SceneBegin(const PerspectiveCamera& camera);
		static void SceneEnd();   
		static void Submit(
			const std::shared_ptr<VertexArray>&		vertexArray,
			const std::shared_ptr<Shader>&			shader,
			const glm::mat4&						transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetRendererAPI(); }
	private:
		struct SceneData // 作为接口,在渲染执行前,统一接受场景数据
		{
			glm::mat4 ViewProjectMartrix{1.0f};
			
			SceneData() {}
		};
	private:
		static SceneData* s_SceneData;// 接口结构体指针
	};
}