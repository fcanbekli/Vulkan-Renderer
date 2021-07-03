#pragma once
#include "VulkanBackend/vkBaseRenderPass.h"

namespace hyp_backend {

	BaseRenderPass::BaseRenderPass(hypatia::SceneGraph* sceneGraph)
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

		if (vkCreateRenderPass(RendererBackend::GetDevice(), &renderPassInfo, nullptr, &RenderPass::m_BaseRenderPass) != VK_SUCCESS) {
			throw std::runtime_error("failed to create render pass!");
		}
	}

	void BaseRenderPass::Draw(uint32_t nextImageIndex)
	{
		for (int i = 0; i < m_SceneGraph->m_Entities.size(); i++) {
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(m_SceneGraph->m_Entities.at(i)->m_CommandBuffer, &beginInfo) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to begin recording command buffer!");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = RenderPass::m_BaseRenderPass;
			renderPassInfo.framebuffer = hypatia::PresentationSystem::GetSwapChainFrameBuffers().at(nextImageIndex);
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = hypatia::PresentationSystem::GetSwapChainExtent();

			VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearColor;

			vkCmdBeginRenderPass(m_SceneGraph->m_Entities.at(i)->m_CommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			vkCmdBindPipeline(m_SceneGraph->m_Entities.at(i)->m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_SceneGraph->m_Entities.at(i)->m_Material->m_Shader->m_Pipeline);

			VkBuffer vertexBuffers[] = { m_SceneGraph->m_Entities.at(i)->m_Model->GetVertexBuffer()};
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(m_SceneGraph->m_Entities.at(i)->m_CommandBuffer, 0, 1, vertexBuffers, offsets);

			vkCmdDraw(m_SceneGraph->m_Entities.at(i)->m_CommandBuffer, static_cast<uint32_t>(m_SceneGraph->m_Entities.at(i)->m_Model->GetVertexData().size()), 1, 0, 0);

			vkCmdEndRenderPass(m_SceneGraph->m_Entities.at(i)->m_CommandBuffer);

			if (vkEndCommandBuffer(m_SceneGraph->m_Entities.at(i)->m_CommandBuffer) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to record command buffer!");
			}

			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

			VkSemaphore waitSemaphores[] = { nullptr }; // imageData->imageAvailableSemaphores[hypatia::PresentationSystem::GetCurrentFrame()]
			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
			submitInfo.waitSemaphoreCount = 0;
			submitInfo.pWaitSemaphores = waitSemaphores;
			submitInfo.pWaitDstStageMask = waitStages;

			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &m_SceneGraph->m_Entities.at(i)->m_CommandBuffer;

			VkSemaphore signalSemaphores[] = { nullptr }; // imageData->renderFinishedSemaphores[hypatia::PresentationSystem::GetCurrentFrame()]
			submitInfo.signalSemaphoreCount = 0;
			submitInfo.pSignalSemaphores = signalSemaphores;

			//vkResetFences(RendererBackend::GetDevice(), 1, &imageData->inFlightFences[hypatia::PresentationSystem::GetCurrentFrame()]);	
			if (vkQueueSubmit(RendererBackend::GetGraphicsQueue(), 1, &submitInfo, nullptr) != VK_SUCCESS) //imageData->inFlightFences[hypatia::PresentationSystem::GetCurrentFrame()]
			{
				throw std::runtime_error("failed to submit draw command buffer!");
			}
		}
		
	}
}