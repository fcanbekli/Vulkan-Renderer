#pragma once
#include "PresentationSystem.h"

namespace hypatia
{
	uint32_t PresentationSystem::GetNextImage()
	{
		//vkAcquireNextImageKHR(hyp_backend::RendererBackend::GetDevice(), m_SwapChain, UINT64_MAX, image_data.imageAvailableSemaphores[image_data.currentFrame], VK_NULL_HANDLE, &m_ImageIndex);
		return m_ImageIndex;
	}

	void PresentationSystem::CreateSwapChain()
	{
		hyp_backend::SwapChainSupportDetails swapChainSupport = hyp_backend::RendererBackend::GetSwapChainSupportDetails();

		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = hyp_backend::RendererBackend::GetSurface();

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		hyp_backend::QueueFamilyIndices indices = hyp_backend::RendererBackend::FindQueueFamilies(hyp_backend::RendererBackend::GetPhysicalDevice());
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(hyp_backend::RendererBackend::GetDevice(), &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain!");
		}

		vkGetSwapchainImagesKHR(hyp_backend::RendererBackend::GetDevice(), m_SwapChain, &imageCount, nullptr);
		m_SwapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(hyp_backend::RendererBackend::GetDevice(), m_SwapChain, &imageCount, m_SwapChainImages.data());

		m_SwapChainImageFormat = surfaceFormat.format;
		m_SwapChainExtent = extent;
	}


	VkSurfaceFormatKHR PresentationSystem::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{

	}


	VkPresentModeKHR PresentationSystem::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{

	}


	VkExtent2D PresentationSystem::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{

	}

}
