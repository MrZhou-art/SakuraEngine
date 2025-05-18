#include "sakuraPCH.h"
#include "Renderer.h"

namespace Sakura
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	/*void Renderer::SceneBegin(const OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectMartrix = camera.GetViewProjectMartix();
	}*/
	void Renderer::SceneBegin(const PerspectiveCamera& camera)
	{
		s_SceneData->ViewProjectMartrix = camera.GetViewProjectMartix();
	}

	void Renderer::SceneEnd()
	{

	}

	void Renderer::Submit(
		const std::shared_ptr<VertexArray>&		vertexArray,
		const std::shared_ptr<Shader>&			shader,
		const glm::mat4&						transform)
	{
		shader->Bind();
		shader->UploadUniform_Mat4(s_SceneData->ViewProjectMartrix, "u_ViewProjectMartrix");
		shader->UploadUniform_Mat4(transform, "u_Transform");

		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}
}