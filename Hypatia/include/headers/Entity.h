#pragma once
#include "pch.h"
#include "Material.h"
#include "VulkanBackend/vkModel.h"
namespace hypatia{
	class Entity {
	public:
		Entity();


		Material* m_Material;
		hyp_backend::Model* m_Model;
		VkCommandBuffer m_CommandBuffer;
	};
}
