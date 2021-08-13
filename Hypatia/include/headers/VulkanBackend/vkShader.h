#pragma once
#include "pch.h"
#include "vkModel.h"
#include "PresentationSystem.h"
#include "VulkanBackend/vkRenderer.h"

namespace hyp_backend {

	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};


	class Shader {
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);

		VkPipeline m_Pipeline;
		VkPipelineLayout m_PipelineLayout;
		UniformBufferObject m_UniformObject;

		VkDescriptorSetLayout m_DescriptorSetLayout;
		VkBuffer m_UniformBuffer;
		VkDeviceMemory m_UniformBuffersMemory;
		VkDescriptorSet m_DescriptorSet;
		VkDescriptorPool m_DescriptorPool;
	private:
		void CreateDescriptor();
		void CreateUniformBuffers();
		void CreateGraphicsPipeline(const std::string& vertexPath, const std::string& fragmentPath);
		VkShaderModule CreateShaderModule(const std::vector<char>& code);
		std::vector<char> ReadFile(const std::string& filename);
	};
}