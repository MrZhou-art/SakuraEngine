#include "sakuraPCH.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Sakura
{
	OrthographicCamera::OrthographicCamera(
		const float& left, const float& right,
		const float& bottom, const float& top)
		: 
		m_ProjectMatrix(glm::ortho(left, right, bottom, top, 1.0f, -1.0f)),
		m_ViewMatrix(1.0f),
		m_Position(0.0f),
		m_Rotation(0.0f)
	{
		m_ViewProjectMatrix = m_ProjectMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecaculateViewProjectMatrix()
	{
		// 计算视图矩阵
		m_ViewMatrix = 
			glm::rotate(glm::mat4(1.0f), glm::radians(-m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::translate(glm::mat4(1.0f), -m_Position);

		// 视图投影矩阵 = 投影矩阵 * 视图矩阵
		m_ViewProjectMatrix = m_ProjectMatrix * m_ViewMatrix;
	}
}