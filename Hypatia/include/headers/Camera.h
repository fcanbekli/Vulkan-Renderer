#pragma once
#include "pch.h"
namespace hypatia{
	class Camera {
	public:
		Camera();
		void Update();
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;

		float m_Width;
		float m_Height;
	};
}
