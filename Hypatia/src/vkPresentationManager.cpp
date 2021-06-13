#pragma once
#include "VulkanBackend/vkPresentationManager.h"

namespace hyp_vlk
{
	namespace hyp_backend {

		PresentationManager::PresentationManager() {}

		void PresentationManager::CreateWin32Surface(VkInstance instance, HWND hWindow, HINSTANCE hInstance) {
			VkWin32SurfaceCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			createInfo.hwnd = (HWND)hWindow;
			createInfo.hinstance = (HINSTANCE)hInstance;

			if (vkCreateWin32SurfaceKHR(instance, &createInfo, NULL, &m_surface) != VK_SUCCESS) {
				throw std::runtime_error("failed to create window surface!");
			}
		}
	}
}