#include "sakuraPCH.h"
#include "RendererCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sakura
{
	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI();
}