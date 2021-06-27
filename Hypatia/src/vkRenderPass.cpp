#pragma once
#include "VulkanBackend/vkRenderPass.h"

namespace hyp_vlk
{
	namespace hyp_backend {
		VkRenderPass RenderPass::m_RenderPass;

		void RenderPass::InitializeRenderPass()
		{
			VkAttachmentDescription colorAttachment{};
			colorAttachment.format = image_data.swapChainImageFormat;
			colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
			colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

			VkAttachmentReference colorAttachmentRef{};
			colorAttachmentRef.attachment = 0;
			colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			VkSubpassDescription subpass{};
			subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			subpass.colorAttachmentCount = 1;
			subpass.pColorAttachments = &colorAttachmentRef;

			VkRenderPassCreateInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			renderPassInfo.attachmentCount = 1;
			renderPassInfo.pAttachments = &colorAttachment;
			renderPassInfo.subpassCount = 1;
			renderPassInfo.pSubpasses = &subpass;

			if (vkCreateRenderPass(device_data.device, &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS) {
				throw std::runtime_error("failed to create render pass!");
			}

			CreateImageBuffer();
			InitializeFrameBuffer();
		}

		void RenderPass::CreateImageBuffer()
		{
			VkImageCreateInfo imageCreateInfo = {};

			imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;

			imageCreateInfo.pNext = NULL;

			imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;

			imageCreateInfo.format = image_data.swapChainImageFormat; // VK_FORMAT_R8G8B8_UINT : this is what I'm suspecting is wrong

			imageCreateInfo.mipLevels = 1; // 1

			imageCreateInfo.arrayLayers = 1;

			imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;

			imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

			imageCreateInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT;

			imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;

			imageCreateInfo.extent = { hyp_backend::image_data.swapChainExtent.width, hyp_backend::image_data.swapChainExtent.height, 1 }; //960, 960, loaded from png via stb_image

			imageCreateInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
			if (vkCreateImage(device_data.device, &imageCreateInfo, NULL, &m_Image) != VK_SUCCESS) {
				throw std::runtime_error("failed to create image views!");
			}
				
			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_Image;
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = image_data.swapChainImageFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(device_data.device, &createInfo, nullptr, &m_ImageView) != VK_SUCCESS) {
				throw std::runtime_error("failed to create image views!");
			}

		}

		void RenderPass::InitializeFrameBuffer()
		{
			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_RenderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = &m_ImageView;
			framebufferInfo.width = hyp_backend::image_data.swapChainExtent.width;
			framebufferInfo.height = hyp_backend::image_data.swapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(hyp_backend::device_data.device, &framebufferInfo, nullptr, &m_Framebuffer) != VK_SUCCESS) {
				throw std::runtime_error("failed to create framebuffer!");
			}
		}

		void RenderPass::Draw()
		{
			std::vector<Entity*> entities = hypatia::SceneGraph::GetEntities(hypatia::ERenderLayer::kBaseLayer);
			for (Entity* entity:entities)
			{
				uint32_t imageIndex;
				vkAcquireNextImageKHR(device_data.device, image_data.swapChain, UINT64_MAX, nullptr, VK_NULL_HANDLE, &imageIndex);

				VkCommandBufferBeginInfo beginInfo{};
				beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

				if (vkBeginCommandBuffer(entity->m_CommandBuffer, &beginInfo) != VK_SUCCESS) {
					throw std::runtime_error("failed to begin recording command buffer!");
				}

				VkRenderPassBeginInfo renderPassInfo{};
				renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
				renderPassInfo.renderPass = m_RenderPass;
				renderPassInfo.framebuffer = m_Framebuffer;	//swapChainFramebuffers[imageIndex];
				renderPassInfo.renderArea.offset = { 0, 0 };
				renderPassInfo.renderArea.extent = image_data.swapChainExtent;

				VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
				renderPassInfo.clearValueCount = 1;
				renderPassInfo.pClearValues = &clearColor;

				vkCmdBeginRenderPass(entity->m_CommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

				vkCmdBindPipeline(entity->m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, entity->m_Material.m_Shader.m_GraphicPipeline);

				vkCmdDraw(entity->m_CommandBuffer, 3, 1, 0, 0);

				vkCmdEndRenderPass(entity->m_CommandBuffer);

				if (vkEndCommandBuffer(entity->m_CommandBuffer) != VK_SUCCESS) {
					throw std::runtime_error("failed to record command buffer!");
				}

				VkSubmitInfo submitInfo{};
				submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
				submitInfo.commandBufferCount = 1;
				submitInfo.pCommandBuffers = &entity->m_CommandBuffer;
				submitInfo.signalSemaphoreCount = 0;
				submitInfo.pSignalSemaphores = nullptr;

				if (vkQueueSubmit(device_data.graphicsQueue, 1, &submitInfo, image_data.inFlightFences[image_data.currentFrame]) != VK_SUCCESS) {
					throw std::runtime_error("failed to submit draw command buffer!");
				}

				VkPresentInfoKHR presentInfo{};
				presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

				presentInfo.waitSemaphoreCount = 0;
				presentInfo.pWaitSemaphores = nullptr;
				VkSwapchainKHR swapChains[] = { image_data.swapChain };
				presentInfo.swapchainCount = 1;
				presentInfo.pSwapchains = swapChains;
				presentInfo.pImageIndices = &imageIndex;

				vkQueuePresentKHR(device_data.presentQueue, &presentInfo);

				image_data.currentFrame = (image_data.currentFrame + 1) % image_data.MAX_FRAMES_IN_FLIGHT;
			}
		}
	}
}
