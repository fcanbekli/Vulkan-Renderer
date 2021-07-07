#pragma once
#include "pch.h"
#include "Camera.h"
namespace hypatia{

	Camera::Camera()
	{
		m_Width = 1920;
		m_Height = 1080;
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ProjectionMatrix = glm::perspective(45.0f, m_Width / m_Height, 1.0f, 150.0f);
	}

	void Camera::Update()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
}
