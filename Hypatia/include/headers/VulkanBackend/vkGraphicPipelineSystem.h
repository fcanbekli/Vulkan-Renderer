#pragma once
#include "VulkanBackend/vkData.h"
namespace hyp_vlk
{
	namespace hyp_backend {
		class GraphicPipelineSystem {
		public:
			GraphicPipelineSystem(){}
			static void CreateGraphicsPipeline(DeviceData* device, ImageData* image);
			static void CreateRenderPass(DeviceData* device, ImageData* image);
		private:
			static VkShaderModule CreateShaderModule(DeviceData* device, const std::vector<char>& code);
			static std::vector<char> ReadFile(const std::string& filename);

		};
	}
} 