#pragma once
#include "VulkanBackend/vkRenderer.h"
namespace hypatia
{
	class PresentationSystem {
		friend class RendererBackend;
	public:
		PresentationSystem(){}
		uint32_t GetNextImage();

			
	private:
		void CreateSwapChain();
		VkSwapchainKHR m_SwapChain;
		std::vector<VkImage> m_SwapChainImages;
		VkFormat m_SwapChainImageFormat;
		VkExtent2D m_SwapChainExtent;
		std::vector<VkImageView> swapChainImageViews;



		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		uint32_t m_ImageIndex;

	};

} 