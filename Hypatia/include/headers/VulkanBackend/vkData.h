#pragma once
#include <memory>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace hypatia
{
	namespace hyp_backend {






		struct WindowData {
			HWND hWindow;
			HINSTANCE hInstance;
			VkSurfaceKHR surface;
			int frameBufferWidth;
			int frameBufferHeight;
		};

		struct ImageData{
			//Pipeline
			VkRenderPass renderPass;
			VkPipelineLayout pipelineLayout;
			VkPipeline graphicsPipeline;

			VkCommandPool commandPool;
			//std::vector<VkCommandBuffer> commandBuffers;

			VkSemaphore imageAvailableSemaphore;
			VkSemaphore renderFinishedSemaphore;

			std::vector<VkSemaphore> imageAvailableSemaphores;
			std::vector<VkSemaphore> renderFinishedSemaphores;

			std::vector<VkFence> inFlightFences;
			std::vector<VkFence> imagesInFlight;
			const int MAX_FRAMES_IN_FLIGHT = 2;
			
		};
		extern WindowData window_data;
		extern ImageData  image_data;
	}
}