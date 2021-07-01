#pragma once
#include "iostream"
#include "pch.h"
#ifdef USE_VULKAN
#include "VulkanBackend/vkData.h"
using namespace hypatia;
#endif

namespace hypatia{
	namespace hyp_backend {

		class Entity {
		public:
			Entity(std::string entityName);
			std::string m_EntityName;

			VkCommandBuffer m_CommandBuffer;

		};
	}
}
