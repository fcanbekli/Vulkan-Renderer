#pragma once
#include "iostream"
#include "pch.h"
#ifdef USE_VULKAN
#include "VulkanBackend/vkData.h"
using namespace hyp_vlk;
#endif

namespace hyp_vlk{
	namespace hyp_backend {

		class Entity {
		public:
			Entity(std::string entityName);
			std::string m_EntityName;

			VkCommandBuffer m_CommandBuffer;

		};
	}
}
