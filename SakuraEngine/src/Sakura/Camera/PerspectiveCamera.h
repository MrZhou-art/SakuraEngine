#pragma once

#include <glm/glm.hpp>

namespace Sakura
{
	class PerspectiveCamera
	{
	public:
		/*
		*	nearPlane;	//近平面
		*	farPlane;	//远平面
		*	fovy;		//垂直视野角度
		*	aspect;		//视口横纵比
		*/
		PerspectiveCamera(
			const float& fovy,		const float& aspect,
			const float& nearPlane,	const float& farPlane);
		~PerspectiveCamera() {}

		const glm::mat4& GetViewMatrix()		const { return m_ViewMatrix; }
		const glm::mat4& GetProjectMatrix()		const { return m_ProjectMatrix; }
		const glm::mat4& GetViewProjectMartix()	const { return m_ViewProjectMatrix; }

		const glm::vec3& GetRightVector()		const { return m_RotationMatrix * glm::vec4(m_Right,0.0f); }
		const glm::vec3& GetUpVector()			const { return m_RotationMatrix * glm::vec4(m_Up, 0.0f); }
		const glm::vec3& GetForwardVector()		const {	return glm::cross(GetRightVector(), GetUpVector());}

		void SetPosition(const glm::vec3& position) { m_Position = position; RecaculateViewProjectMatrix(); }
		const glm::vec3& GetPosition()		const	{ return m_Position; }

		void SetRotation(const glm::vec3& axile, const float& angle);
	private:
		void RecaculateViewProjectMatrix(); // 在每次设置位置和旋转之后,更新矩阵
	private:
		glm::mat4 m_ViewMatrix;			//视角矩阵(世界空间转为摄像机空间)
		glm::mat4 m_ProjectMatrix;		//投影矩阵(投影盒子)
		glm::mat4 m_ViewProjectMatrix;

		glm::vec3 m_Position{ 0.0f,0.0f,0.0f };	//位置(世界坐标系)
		glm::vec3 m_Right	{ 1.0f,0.0f,0.0f };	//右向量(相机坐标系)
		glm::vec3 m_Up		{ 0.0f,1.0f,0.0f };	//上向量(相机坐标系)

		glm::mat4 m_RotationMatrix;				//相机旋转矩阵
	};
}