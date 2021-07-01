#pragma once
#include "VulkanBackend/vkBaseRenderPass.h"

namespace hypatia
{
	namespace hyp_backend {

		BaseRenderPass::BaseRenderPass(SceneGraph* sceneGraph)
			:m_SceneGraph(sceneGraph)
		{
			InitRenderPass();
		}

		void BaseRenderPass::InitRenderPass() 
		{
			VkAttachmentDescription colorAttachment{};
			colorAttachment.format = hypatia::PresentationSystem::GetSwapChainImageFormat();
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

			if (vkCreateRenderPass(RendererBackend::GetDevice(), &renderPassInfo, nullptr, &m_Renderpass) != VK_SUCCESS) {
				throw std::runtime_error("failed to create render pass!");
			}
		}

		void BaseRenderPass::Draw(uint32_t nextImageIndex)
		{
			for (auto entity : m_SceneGraph->m_Entities)
			{
				VkCommandBufferBeginInfo beginInfo{};
				beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

				if (vkBeginCommandBuffer(entity->m_CommandBuffer, &beginInfo) != VK_SUCCESS)
				{
					throw std::runtime_error("failed to begin recording command buffer!");
				}

				VkRenderPassBeginInfo renderPassInfo{};
				renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
				renderPassInfo.renderPass = m_Renderpass;
				renderPassInfo.framebuffer = hypatia::PresentationSystem::GetSwapChainFrameBuffers().at(nextImageIndex);
				renderPassInfo.renderArea.offset = { 0, 0 };
				renderPassInfo.renderArea.extent = hypatia::PresentationSystem::GetSwapChainExtent();

				VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
				renderPassInfo.clearValueCount = 1;
				renderPassInfo.pClearValues = &clearColor;

				vkCmdBeginRenderPass(entity->m_CommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

				vkCmdBindPipeline(entity->m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, imageData->graphicsPipeline);

				vkCmdDraw(entity->m_CommandBuffer, 3, 1, 0, 0);

				vkCmdEndRenderPass(entity->m_CommandBuffer);

				if (vkEndCommandBuffer(entity->m_CommandBuffer) != VK_SUCCESS)
				{
					throw std::runtime_error("failed to record command buffer!");
				}

				VkSubmitInfo submitInfo{};
				submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

				VkSemaphore waitSemaphores[] = { imageData->imageAvailableSemaphores[hypatia::PresentationSystem::GetCurrentFrame()] };
				VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
				submitInfo.waitSemaphoreCount = 1;
				submitInfo.pWaitSemaphores = waitSemaphores;
				submitInfo.pWaitDstStageMask = waitStages;

				submitInfo.commandBufferCount = 1;
				submitInfo.pCommandBuffers = &entity->m_CommandBuffer;

				VkSemaphore signalSemaphores[] = { imageData->renderFinishedSemaphores[hypatia::PresentationSystem::GetCurrentFrame()] };
				submitInfo.signalSemaphoreCount = 1;
				submitInfo.pSignalSemaphores = signalSemaphores;

				vkResetFences(RendererBackend::GetDevice(), 1, &imageData->inFlightFences[hypatia::PresentationSystem::GetCurrentFrame()]);

				if (vkQueueSubmit(RendererBackend::GetGraphicsQueue(), 1, &submitInfo, imageData->inFlightFences[hypatia::PresentationSystem::GetCurrentFrame()]) != VK_SUCCESS)
				{
					throw std::runtime_error("failed to submit draw command buffer!");
				}
			}
			}
		
		}
}


