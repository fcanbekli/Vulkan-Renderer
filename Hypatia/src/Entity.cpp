#include "Entity.h"

namespace hypatia {
	namespace hyp_backend {
		Entity::Entity(std::string entityName)
		{
			VkCommandBufferAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.commandPool = hyp_backend::image_data.commandPool;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandBufferCount = 1;

			if (vkAllocateCommandBuffers(hyp_backend::device_data.device, &allocInfo, &m_CommandBuffer) != VK_SUCCESS) {
				throw std::runtime_error("failed to allocate command buffers!");
			}

			m_EntityName = entityName;
		}
	}
}


