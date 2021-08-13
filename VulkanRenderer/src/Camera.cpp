#pragma once
#include "pch.h"
#include "Camera.h"
namespace hypatia{

	Camera::Camera()
	{
		m_Position = glm::vec3(0);
		m_Width = 1920;
		m_Height = 1080;
		m_ViewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		float x = (float)PresentationSystem::GetSwapChainExtent().width;
		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)PresentationSystem::GetSwapChainExtent().width / (float)PresentationSystem::GetSwapChainExtent().height, 0.1f, 10.0f);
	}

	void Camera::Update()
	{

	}
}
