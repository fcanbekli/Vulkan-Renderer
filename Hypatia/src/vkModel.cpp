#include "vulkanBackend/vkModel.h"

namespace hyp_backend {

	Model::Model()
	{
		CreateVertexBuffer();
		CreateIndexBuffer();
	}

	void Model::Load()
	{

	}

	void Model::CreateVertexBuffer() {
		VkDeviceSize bufferSize = sizeof(m_Vertices[0]) * m_Vertices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		RendererBackend::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(RendererBackend::GetDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, m_Vertices.data(), (size_t)bufferSize);
		vkUnmapMemory(RendererBackend::GetDevice(), stagingBufferMemory);

		RendererBackend::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_VertexBuffer, m_VertexBufferMemory);

		CopyBuffer(stagingBuffer, m_VertexBuffer, bufferSize);

		vkDestroyBuffer(RendererBackend::GetDevice(), stagingBuffer, nullptr);
		vkFreeMemory(RendererBackend::GetDevice(), stagingBufferMemory, nullptr);
	}

	void Model::CreateIndexBuffer()
	{
		VkDeviceSize bufferSize = sizeof(m_Indices[0]) * m_Indices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		RendererBackend::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(RendererBackend::GetDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, m_Indices.data(), (size_t)bufferSize);
		vkUnmapMemory(RendererBackend::GetDevice(), stagingBufferMemory);

		RendererBackend::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_IndexBuffer, m_IndexBufferMemory);

		CopyBuffer(stagingBuffer, m_IndexBuffer, bufferSize);

		vkDestroyBuffer(RendererBackend::GetDevice(), stagingBuffer, nullptr);
		vkFreeMemory(RendererBackend::GetDevice(), stagingBufferMemory, nullptr);
	}


	void Model::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = RendererBackend::GetCommandPool();
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(RendererBackend::GetDevice(), &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		VkBufferCopy copyRegion{};
		copyRegion.size = size;
		vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(RendererBackend::GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(RendererBackend::GetGraphicsQueue());

		vkFreeCommandBuffers(RendererBackend::GetDevice(), RendererBackend::GetCommandPool(), 1, &commandBuffer);
	}

}
