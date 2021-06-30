#pragma once
#include "VulkanBackend/vkPresentationSystem.h"

namespace hyp_vlk
{
	namespace hyp_backend {

		PresentationSystem::PresentationSystem() {}

		void PresentationSystem::CreateWin32Surface(WindowData* windowData, DeviceData* deviceData) {
			VkWin32SurfaceCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			createInfo.hwnd = windowData->hWindow;
			createInfo.hinstance = windowData->hInstance;

			if (vkCreateWin32SurfaceKHR(deviceData->instance, &createInfo, NULL, &windowData->surface) != VK_SUCCESS) {
				throw std::runtime_error("failed to create window surface!");
			}
		}

		void PresentationSystem::CreateSwapChain(DeviceData* deviceData, ImageData* imageData, WindowData* windowData)
		{
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(deviceData->physicalDevice);

            VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
            VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
            VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

            uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
            if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
                imageCount = swapChainSupport.capabilities.maxImageCount;
            }

            VkSwapchainCreateInfoKHR createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            createInfo.surface = windowData->surface;

            createInfo.minImageCount = imageCount;
            createInfo.imageFormat = surfaceFormat.format;
            createInfo.imageColorSpace = surfaceFormat.colorSpace;
            createInfo.imageExtent = extent;
            createInfo.imageArrayLayers = 1;
            createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

            QueueFamilyIndices indices = DeviceSystem::findQueueFamilies(deviceData->physicalDevice);
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

            if (vkCreateSwapchainKHR(deviceData->device, &createInfo, nullptr, &imageData->swapChain) != VK_SUCCESS) {
                throw std::runtime_error("failed to create swap chain!");
            }

            vkGetSwapchainImagesKHR(deviceData->device, imageData->swapChain, &imageCount, nullptr);
            imageData->swapChainImages.resize(imageCount);
            vkGetSwapchainImagesKHR(deviceData->device, imageData->swapChain, &imageCount, imageData->swapChainImages.data());

            imageData->swapChainImageFormat = surfaceFormat.format;
            imageData->swapChainExtent = extent;
        }

        void PresentationSystem::CreateImageBuffer(DeviceData* deviceData, ImageData* imageData)
		{
            imageData->swapChainImageViews.resize(imageData->swapChainImages.size());

            for (size_t i = 0; i < imageData->swapChainImages.size(); i++) {
                VkImageViewCreateInfo createInfo{};
                createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                createInfo.image = imageData->swapChainImages[i];
                createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
                createInfo.format = imageData->swapChainImageFormat;
                createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
                createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
                createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
                createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
                createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                createInfo.subresourceRange.baseMipLevel = 0;
                createInfo.subresourceRange.levelCount = 1;
                createInfo.subresourceRange.baseArrayLayer = 0;
                createInfo.subresourceRange.layerCount = 1;

                if (vkCreateImageView(deviceData->device, &createInfo, nullptr, &imageData->swapChainImageViews[i]) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create image views!");
                }
            }
		}

		void PresentationSystem::CreateFrameBuffer(DeviceData* deviceData, ImageData* imageData)
		{
            imageData->swapChainFramebuffers.resize(imageData->swapChainImageViews.size());

            for (size_t i = 0; i < imageData->swapChainImageViews.size(); i++) {
                VkImageView attachments[] = {
                     imageData->swapChainImageViews[i]
                };

                VkFramebufferCreateInfo framebufferInfo{};
                framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
                framebufferInfo.renderPass = imageData->renderPass;
                framebufferInfo.attachmentCount = 1;
                framebufferInfo.pAttachments = attachments;
                framebufferInfo.width = imageData->swapChainExtent.width;
                framebufferInfo.height = imageData->swapChainExtent.height;
                framebufferInfo.layers = 1;

                if (vkCreateFramebuffer(deviceData->device, &framebufferInfo, nullptr, &imageData->swapChainFramebuffers[i]) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create framebuffer!");
                }
            }
		}

		void PresentationSystem::CreateCommandPool(DeviceData* deviceData, ImageData* imageData)
		{
            QueueFamilyIndices queueFamilyIndices = DeviceSystem::findQueueFamilies(deviceData->physicalDevice);

            VkCommandPoolCreateInfo poolInfo{};
            poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

            if (vkCreateCommandPool(deviceData->device, &poolInfo, nullptr, &imageData->commandPool) != VK_SUCCESS) {
                throw std::runtime_error("failed to create command pool!");
            }
		}

		void PresentationSystem::CreateCommandBuffer(DeviceData* deviceData, ImageData* imageData)
		{
            imageData->commandBuffers.resize(imageData->swapChainFramebuffers.size());

            VkCommandBufferAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            allocInfo.commandPool = imageData->commandPool;
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            allocInfo.commandBufferCount = (uint32_t)imageData->commandBuffers.size();

            if (vkAllocateCommandBuffers(deviceData->device, &allocInfo, imageData->commandBuffers.data()) != VK_SUCCESS) {
                throw std::runtime_error("failed to allocate command buffers!");
            }
		}

		void PresentationSystem::CreateSyncObjects(DeviceData* deviceData, ImageData* imageData)
		{
            imageData->imageAvailableSemaphores.resize(imageData->MAX_FRAMES_IN_FLIGHT);
            imageData->renderFinishedSemaphores.resize(imageData->MAX_FRAMES_IN_FLIGHT);
            imageData->inFlightFences.resize(imageData->MAX_FRAMES_IN_FLIGHT);
            imageData->imagesInFlight.resize(imageData->swapChainImages.size(), VK_NULL_HANDLE);

            VkSemaphoreCreateInfo semaphoreInfo{};
            semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

            VkFenceCreateInfo fenceInfo{};
            fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
            fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

            for (size_t i = 0; i < imageData->MAX_FRAMES_IN_FLIGHT; i++) {
                if (vkCreateSemaphore(deviceData->device, &semaphoreInfo, nullptr, &imageData->imageAvailableSemaphores[i]) != VK_SUCCESS ||
                    vkCreateSemaphore(deviceData->device, &semaphoreInfo, nullptr, &imageData->renderFinishedSemaphores[i]) != VK_SUCCESS ||
                    vkCreateFence(deviceData->device, &fenceInfo, nullptr, &imageData->inFlightFences[i]) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create synchronization objects for a frame!");
                }
            }
		}




        


		void PresentationSystem::DrawFrame(DeviceData* deviceData, ImageData* imageData)
		{


			vkAcquireNextImageKHR(deviceData->device, imageData->swapChain, UINT64_MAX, imageData->imageAvailableSemaphores[imageData->currentFrame], VK_NULL_HANDLE, &imageData->imageIndex);
 
		}


		void PresentationSystem::PresentFrame(DeviceData* deviceData, ImageData* imageData)
		{
			VkPresentInfoKHR presentInfo{};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

			presentInfo.waitSemaphoreCount = 0;
			presentInfo.pWaitSemaphores = nullptr;

			VkSwapchainKHR swapChains[] = { imageData->swapChain };
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = swapChains;

			presentInfo.pImageIndices = &imageData->imageIndex;

			vkQueuePresentKHR(deviceData->presentQueue, &presentInfo);
			imageData->currentFrame = (imageData->currentFrame + 1) % imageData->MAX_FRAMES_IN_FLIGHT;
		}

		SwapChainSupportDetails PresentationSystem::querySwapChainSupport(VkPhysicalDevice device) {
            SwapChainSupportDetails details;

            vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, window_data.surface, &details.capabilities);

            uint32_t formatCount;
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, window_data.surface, &formatCount, nullptr);

            if (formatCount != 0) {
                details.formats.resize(formatCount);
                vkGetPhysicalDeviceSurfaceFormatsKHR(device, window_data.surface, &formatCount, details.formats.data());
            }

            uint32_t presentModeCount;
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, window_data.surface, &presentModeCount, nullptr);

            if (presentModeCount != 0) {
                details.presentModes.resize(presentModeCount);
                vkGetPhysicalDeviceSurfacePresentModesKHR(device, window_data.surface, &presentModeCount, details.presentModes.data());
            }

            return details;
        }

        VkSurfaceFormatKHR PresentationSystem::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
            for (const auto& availableFormat : availableFormats) {
                if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                    return availableFormat;
                }
            }

            return availableFormats[0];
        }

        VkPresentModeKHR PresentationSystem::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
            for (const auto& availablePresentMode : availablePresentModes) {
                if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                    return availablePresentMode;
                }
            }

            return VK_PRESENT_MODE_FIFO_KHR;
        }


        VkExtent2D PresentationSystem::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
            if (capabilities.currentExtent.width != UINT32_MAX) {
                return capabilities.currentExtent;
            }
            else {
               

                VkExtent2D actualExtent = {
                    static_cast<uint32_t>(window_data.frameBufferWidth),
                    static_cast<uint32_t>(window_data.frameBufferHeight)
                };

                actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
                actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

                return actualExtent;
            }
        }

		
			
		}
	}
