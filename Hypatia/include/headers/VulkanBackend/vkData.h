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
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

		struct DeviceData {
			VkInstance instance;
			VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
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
		};
		extern DeviceData device_data;
		extern WindowData window_data;
		extern ImageData  image_data;
	}
}