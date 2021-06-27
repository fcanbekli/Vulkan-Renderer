#include "VulkanBackend/vkBufferFactory.h"

namespace hyp_vlk
{
	namespace hyp_backend {
		void BufferFactory::CreateCommandBuffer(VkCommandBuffer& buffer)
		{
			VkCommandBufferAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.commandPool = image_data.commandPool;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandBufferCount = 1;

			if (vkAllocateCommandBuffers(device_data.device, &allocInfo, &buffer) != VK_SUCCESS) {
				throw std::runtime_error("failed to allocate command buffers!");
			}
		}
	}
}