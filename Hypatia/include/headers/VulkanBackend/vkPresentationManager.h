#pragma once
#include "VulkanBackend/vkDeviceManager.h"
#include "VulkanBackend/vkData.h"
namespace hyp_vlk
{
	namespace hyp_backend {
		class PresentationSystem {
			friend class DeviceSystem;
		public:
			PresentationSystem();

			static void CreateWin32Surface(VkInstance& instance, HWND& hWindow, HINSTANCE& hInstance, VkSurfaceKHR& surface);
			static void CreateSwapChain(VkPhysicalDevice& physicalDevice, VkSurfaceKHR& surface, VkDevice& device, VkFormat& swapChainImageFormat, VkExtent2D& swapChainExtent, std::vector<VkImage>& swapChainImages, VkSwapchainKHR& swapChain);
			static void CreateImageBuffer(VkDevice &device, std::vector<VkImageView> &swapChainImageViews, std::vector<VkImage> &swapChainImages, VkFormat swapChainImageFormat);

		private:
			static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
			static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		};
	}
} 