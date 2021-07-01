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
			uint32_t imageIndex;
			VkSwapchainKHR swapChain;
			std::vector<VkImage> swapChainImages;
			VkFormat swapChainImageFormat;
			VkExtent2D swapChainExtent;
			std::vector<VkImageView> swapChainImageViews;
			std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
			//Pipeline
			VkRenderPass renderPass;
			VkPipelineLayout pipelineLayout;
			VkPipeline graphicsPipeline;
			std::vector<VkFramebuffer> swapChainFramebuffers;

			VkCommandPool commandPool;
			//std::vector<VkCommandBuffer> commandBuffers;

			VkSemaphore imageAvailableSemaphore;
			VkSemaphore renderFinishedSemaphore;

			std::vector<VkSemaphore> imageAvailableSemaphores;
			std::vector<VkSemaphore> renderFinishedSemaphores;

			std::vector<VkFence> inFlightFences;
			std::vector<VkFence> imagesInFlight;
			const int MAX_FRAMES_IN_FLIGHT = 2;
			size_t currentFrame = 0;
		};
		extern WindowData window_data;
		extern ImageData  image_data;
	}
}