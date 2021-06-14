#pragma once
#include <memory>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace hyp_vlk
{
	namespace hyp_backend {
		struct DeviceData {
			VkInstance instance;
			VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
			VkDevice device;
			std::vector<const char*> extensions;
		};

		struct WindowData {
			HWND hWindow;
			HINSTANCE hInstance;
			VkSurfaceKHR surface;
		};

		extern DeviceData device_data;
		extern WindowData surface_data;
	}
}