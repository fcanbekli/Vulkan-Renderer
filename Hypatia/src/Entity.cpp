#include "Entity.h"

namespace hypatia {
	Entity::Entity()
	{
		m_Position = glm::vec3(0);
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = hyp_backend::RendererBackend::GetCommandPool();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(hyp_backend::RendererBackend::GetDevice(), &allocInfo, &m_CommandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}
	}

	void Entity::Update()
	{


		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		hyp_backend::UniformBufferObject ubo{};
		m_Material->m_Shader->m_UniformObject.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		m_Material->m_Shader->m_UniformObject.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		m_Material->m_Shader->m_UniformObject.proj = glm::perspective(glm::radians(45.0f), (float)PresentationSystem::GetSwapChainExtent().width / (float)PresentationSystem::GetSwapChainExtent().height, 0.1f, 10.0f);
		m_Material->m_Shader->m_UniformObject.proj[1][1] *= -1;




		void* data;	
		vkMapMemory(hyp_backend::RendererBackend::GetDevice(), m_Material->m_Shader->m_UniformBuffersMemory, 0, sizeof(m_Material->m_Shader->m_UniformObject), 0, &data);
		memcpy(data, &m_Material->m_Shader->m_UniformObject, sizeof(m_Material->m_Shader->m_UniformObject));
		vkUnmapMemory(hyp_backend::RendererBackend::GetDevice(), m_Material->m_Shader->m_UniformBuffersMemory);


		


	}

}