#include "sakuraPCH.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Sakura
{
	PerspectiveCamera::PerspectiveCamera(
		const float& fovy,		const float& aspect,
		const float& nearPlane, const float& farPlane)
		: 
		m_ViewMatrix(1.0f),
		m_ProjectMatrix(glm::perspective(glm::radians(fovy), aspect, nearPlane, farPlane)),
		m_RotationMatrix(1.0f)
	{
		m_ViewProjectMatrix = m_ViewMatrix * m_ProjectMatrix;
	}

	void PerspectiveCamera::SetRotation(const glm::vec3& axile, const float& angle)
	{
		/*m_Up	= glm::rotate(glm::mat4(1.0f), glm::radians(angle), axile) * glm::vec4(m_Up, 0.0f);
		m_Right = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axile) * glm::vec4(m_Right, 0.0f);*/

		m_RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axile);

		RecaculateViewProjectMatrix();
	}

	void PerspectiveCamera::RecaculateViewProjectMatrix()
	{
		// 计算视图矩阵的旋转部分
		/*
		* glm::vec3 forward = glm::cross(m_Right, m_Up);
		* glm::mat4 rotation = glm::mat4(
		*		glm::vec4(m_Right, 0.0f),
		*		glm::vec4(m_Up, 0.0f),
		*		glm::vec4(-forward, 0.0f), // 注意这里是负的forward，因为相机看向-forward方向
		*		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		* );
		*/

		// 视图矩阵 = 旋转矩阵 * 平移矩阵（注意顺序是相反的）
		m_ViewMatrix = m_RotationMatrix * glm::translate(glm::mat4(1.0f), -m_Position);

		// 视图投影矩阵 = 投影矩阵 * 视图矩阵
		m_ViewProjectMatrix = m_ProjectMatrix * m_ViewMatrix;
	}
}