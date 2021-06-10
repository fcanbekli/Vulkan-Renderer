#pragma once
#include <vulkan/vulkan_core.h>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <optional>
#include "VulkanBackend/vkComputePipeline.h"
#include "VulkanBackend/vkUIPipeline.h"
#include "VulkanBackend/vkPostPipeline.h"
#include "VulkanBackend/vkDrawPipeline.h"
#include "PipelineDesc.h"
namespace hyp_vlk
{
	namespace hyp_backend {

		struct QueueFamilyIndices {
			std::optional<uint32_t> graphicsFamily;

			bool isComplete() {
				return graphicsFamily.has_value();
			}
		};

		class RendererBackend{
		public:
			RendererBackend() {};
			void initRenderer();
			void render();
			void syncRendererOptions(hypatia::PIPELINE_COMPUTE_DESC* computeDesc, hypatia::PIPELINE_DRAW_DESC* drawDesc, hypatia::PIPELINE_POSTPROCESS_DESC* postProcessDecs, hypatia::PIPELINE_UI_DESC* uiDesc);

			DrawPipeline* drawPipeline;
			UIPipeline* uiPipeline;
			ComputePipeline* computePipeline;
			PostPipeline* postPipeline;


			hypatia::PIPELINE_DRAW_DESC* drawDesc;
			hypatia::PIPELINE_UI_DESC* uiDesc;
			hypatia::PIPELINE_COMPUTE_DESC* computeDesc;
			hypatia::PIPELINE_POSTPROCESS_DESC* postProcessDesc;




			//1: Create Instance
			VkInstance instance;
			VkDebugUtilsMessengerEXT debugMessenger;
			VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

			void createInstance();
			void setupDebugMessenger();
			void pickPhysicalDevice();
		};
	}
}