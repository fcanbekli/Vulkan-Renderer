#pragma once
#include "pch.h"
#include "Material.h"

namespace hypatia{
	class Entity {
	public:
		Entity();


		Material* m_Material;
		VkCommandBuffer m_CommandBuffer;
	};
}
