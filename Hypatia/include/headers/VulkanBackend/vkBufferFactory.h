#pragma once
#include "pch.h"
#include "VulkanBackend/vkRenderer.h"
namespace hyp_backend
{
	class BufferFactory {
	public:
		BufferFactory(){}
		static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	};
}
