#pragma once
#include "pch.h"
#include "vkModel.h"
#include "PresentationSystem.h"
#include "VulkanBackend/vkRenderer.h"

namespace hyp_backend {
	class Shader {
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);

		VkPipeline m_Pipeline;
		VkPipelineLayout m_PipelineLayout;
	private:
		void CreateGraphicsPipeline(const std::string& vertexPath, const std::string& fragmentPath);
		VkShaderModule CreateShaderModule(const std::vector<char>& code);
		std::vector<char> ReadFile(const std::string& filename);
	};
}