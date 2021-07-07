#pragma once
#include "pch.h"
#include "Material.h"
#include "SceneGraph.h"
#include "VulkanBackend/vkModel.h"

namespace hypatia{
	class SceneGraph;
	class Entity {
	public:
		
		Entity();
		void Update();
		Material* m_Material;
		hyp_backend::Model* m_Model;

		glm::mat4 m_ModelMatrix;
		VkCommandBuffer m_CommandBuffer;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
	};
}
