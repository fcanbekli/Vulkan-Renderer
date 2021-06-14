#pragma once
#include <memory>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace hyp_vlk
{
	namespace hyp_backend {
		struct Device {
			//TODO:()Smart pointer convertion
			VkInstance instance;
			VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
			VkDevice device;
			std::vector<const char*> extensions;
		};

		static Device device_t;
	}
}