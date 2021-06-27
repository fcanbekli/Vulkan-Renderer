#pragma once
#include "pch.h"
#include "vkData.h"
#include "vkRenderPass.h"

namespace hyp_vlk
{
	namespace hyp_backend {

		class Shader {
		public:
			Shader(); 
			VkPipelineLayout m_PipelineLayout;
			VkPipeline m_GraphicPipeline;
			std::string m_ShaderName;
		private:
			void CreateGraphicsPipeline();
			VkShaderModule CreateShaderModule(const std::vector<char>& code);
			std::vector<char> ReadFile(const std::string& filename);
		};
	}
}