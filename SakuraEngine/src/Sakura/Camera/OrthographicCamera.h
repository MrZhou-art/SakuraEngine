#pragma once

#include <glm/glm.hpp>

namespace Sakura
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(
			const float& left, const float& right,
			const float& bottom, const float& top);
		~OrthographicCamera() {}

		const glm::mat4& GetViewMatrix()		const { return m_ViewMatrix; }
		const glm::mat4& GetProjectMatrix()		const { return m_ProjectMatrix; }
		const glm::mat4& GetViewProjectMartix()	const {	return m_ViewProjectMatrix; }

		void SetPosition(const glm::vec3& position) { m_Position = position; RecaculateViewProjectMatrix(); }
		const glm::vec3& GetPosition()			const { return m_Position; }

		void SetRotation(const float& rotation) { m_Rotation = rotation; RecaculateViewProjectMatrix(); }
		const float&	GetRotation()			const { return m_Rotation; }
	private:
		void RecaculateViewProjectMatrix(); // 在每次设置位置和旋转之后,更新矩阵
	private:
		glm::mat4 m_ViewMatrix;			//视角矩阵(世界空间转为摄像机空间)
		glm::mat4 m_ProjectMatrix;		//投影矩阵(投影盒子)
		glm::mat4 m_ViewProjectMatrix;

		glm::vec3 m_Position;
		float m_Rotation; // 正交相机只需要旋转 Z 轴
	};
}