#pragma once
#include <memory>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace hyp_vlk
{
	namespace hyp_backend {

		struct QueueFamilyIndices {
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;

			bool isComplete() {
				return graphicsFamily.has_value() && presentFamily.has_value();
			}
		};

		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities; //Basic surface capabilities (min/max number of images in swap chain, min/max width and height of images)
			std::vector<VkSurfaceFormatKHR> formats; //Surface formats (pixel format, color space)
			std::vector<VkPresentModeKHR> presentModes; //Available presentation modes
		};

		struct DeviceData {
			VkInstance instance;
			VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
			VkPhysicalDeviceProperties physicalDeviceProperties;
			VkPhysicalDeviceFeatures physicalDeviceFeatures;
			VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
			VkDevice device;
			VkQueue graphicsQueue;
			VkQueue presentQueue;
			std::vector<const char*> extensions;
		};

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
			std::vector<VkCommandBuffer> commandBuffers;

			VkSemaphore imageAvailableSemaphore;
			VkSemaphore renderFinishedSemaphore;

			std::vector<VkSemaphore> imageAvailableSemaphores;
			std::vector<VkSemaphore> renderFinishedSemaphores;

			std::vector<VkFence> inFlightFences;
			std::vector<VkFence> imagesInFlight;
			const int MAX_FRAMES_IN_FLIGHT = 2;
			size_t currentFrame = 0;
		};
		extern DeviceData device_data;
		extern WindowData window_data;
		extern ImageData  image_data;
	}
}