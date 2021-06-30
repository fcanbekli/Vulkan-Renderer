#pragma once
#include "vkData.h"
#include "pch.h"
namespace hypatia
{
	class Entity {
	public:
		Entity();
		std::string m_EntityName;

		VkCommandBuffer m_CommandBuffer;

	};
}