#include "sakuraPCH.h"
#include "Sakura/Renderer/Renderer.h"

namespace Sakura
{
	void Renderer::SceneBegin()
	{

	}
	void Renderer::SceneEnd()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}
}