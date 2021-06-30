#pragma once
#include "VulkanBackend/vkFrameGraph.h"

namespace hypatia
{


	VkFramebuffer FrameGraph::BuildFrame(DeviceData* deviceData, ImageData* imageData)
	{



		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;


		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = imageData->renderPass;
		renderPassInfo.framebuffer = imageData->swapChainFramebuffers[m_NextImageIndex];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = imageData->swapChainExtent;
		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		if (vkBeginCommandBuffer(imageData->commandBuffers[0], &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		vkCmdBeginRenderPass(imageData->commandBuffers[0], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(imageData->commandBuffers[0], VK_PIPELINE_BIND_POINT_GRAPHICS, imageData->graphicsPipeline);

		vkCmdDraw(imageData->commandBuffers[0], 3, 1, 0, 0);

		vkCmdEndRenderPass(imageData->commandBuffers[0]);

		if (vkEndCommandBuffer(imageData->commandBuffers[0]) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { imageData->imageAvailableSemaphores[imageData->currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &imageData->commandBuffers[0];

		VkSemaphore signalSemaphores[] = { imageData->renderFinishedSemaphores[imageData->currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if (vkQueueSubmit(deviceData->graphicsQueue, 1, &submitInfo, nullptr) != VK_SUCCESS) {
			throw std::runtime_error("failed to submit draw command buffer!");
		}

	}

}