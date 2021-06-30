#pragma once
#include "VulkanBackend/vkDeviceSystem.h"
#include "VulkanBackend/vkData.h"
namespace hyp_vlk
{
	namespace hyp_backend {
		class PresentationSystem {
			friend class DeviceSystem;
		public:
			PresentationSystem();

			static void CreateWin32Surface(WindowData* windowData, DeviceData* deviceData);
			static void CreateSwapChain(DeviceData* deviceData, ImageData* imageData, WindowData* windowData);
			static void CreateImageBuffer(DeviceData* deviceData, ImageData* imageData);
			static void CreateFrameBuffer(DeviceData* deviceData, ImageData* imageData);

			static void CreateCommandPool(DeviceData* deviceData, ImageData* imageData);
			static void CreateCommandBuffer(DeviceData* deviceData, ImageData* imageData);

			static void CreateSyncObjects(DeviceData* deviceData, ImageData* imageData);
			static void DrawFrame(DeviceData* deviceData, ImageData* imageData);
			static void PresentFrame(DeviceData* deviceData, ImageData* imageData);
		private:
			static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
			static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		};
	}
} 