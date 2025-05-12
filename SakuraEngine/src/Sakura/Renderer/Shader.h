#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sakura
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		//设置不同类型的 uniform 变量
		void UploadUniform_Mat4(const glm::mat4& matrix4, const std::string & name);
	private:
		uint32_t m_RendererID;
	};
}