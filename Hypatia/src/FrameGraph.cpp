#pragma once
#include "FrameGraph.h"

namespace hypatia
{

	void FrameGraph::InitializeRenderPasses()
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

		if (vkCreateRenderPass(hyp_backend::RendererBackend::GetDevice(), &renderPassInfo, nullptr, &hyp_backend::RendererBackend::m_RenderLayers.m_BaseRenderPass) != VK_SUCCESS) {
			throw std::runtime_error("failed to create render pass!");
		}
	}

	void FrameGraph::BuildFrame()
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(hyp_backend::RendererBackend::GetCommandBuffers().at(m_NextImageIndex), &beginInfo) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = hyp_backend::RendererBackend::GetRenderLayer(ERenderLayer::kBaseLayer);
		renderPassInfo.framebuffer = hypatia::PresentationSystem::GetSwapChainFrameBuffers().at(m_NextImageIndex);
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = hypatia::PresentationSystem::GetSwapChainExtent();

		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(hyp_backend::RendererBackend::GetCommandBuffers().at(m_NextImageIndex), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(hyp_backend::RendererBackend::GetCommandBuffers().at(m_NextImageIndex), VK_PIPELINE_BIND_POINT_GRAPHICS, m_SceneGraph->m_Entities.at(0)->m_Material->m_Shader->m_Pipeline);

		VkBuffer vertexBuffers[] = { m_SceneGraph->m_Entities.at(0)->m_Model->GetVertexBuffer() };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(hyp_backend::RendererBackend::GetCommandBuffers().at(m_NextImageIndex), 0, 1, vertexBuffers, offsets);

		vkCmdBindIndexBuffer(hyp_backend::RendererBackend::GetCommandBuffers().at(m_NextImageIndex), m_SceneGraph->m_Entities.at(0)->m_Model->m_IndexBuffer, 0, VK_INDEX_TYPE_UINT16);

		vkCmdBindDescriptorSets(hyp_backend::RendererBackend::GetCommandBuffers().at(m_NextImageIndex), VK_PIPELINE_BIND_POINT_GRAPHICS, m_SceneGraph->m_Entities.at(0)->m_Material->m_Shader->m_PipelineLayout, 0, 1, &m_SceneGraph->m_Entities.at(0)->m_Material->m_Shader->m_DescriptorSet, 0, nullptr);

		vkCmdDrawIndexed(hyp_backend::RendererBackend::GetCommandBuffers().at(m_NextImageIndex), static_cast<uint32_t>(m_SceneGraph->m_Entities.at(0)->m_Model->m_Indices.size()), 1, 0, 0, 0);


		vkCmdEndRenderPass(hyp_backend::RendererBackend::GetCommandBuffers().at(m_NextImageIndex));

		if (vkEndCommandBuffer(hyp_backend::RendererBackend::GetCommandBuffers().at(m_NextImageIndex)) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to record command buffer!");
		}
	}

	void FrameGraph::SubmitFrame()
	{
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { nullptr }; // imageData->imageAvailableSemaphores[hypatia::PresentationSystem::GetCurrentFrame()]
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 0;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		VkCommandBuffer x = hyp_backend::RendererBackend::GetCommandBuffers().at(m_NextImageIndex);
		submitInfo.pCommandBuffers = &x;

		VkSemaphore signalSemaphores[] = { nullptr }; // imageData->renderFinishedSemaphores[hypatia::PresentationSystem::GetCurrentFrame()]
		submitInfo.signalSemaphoreCount = 0;
		submitInfo.pSignalSemaphores = signalSemaphores;

		//vkResetFences(RendererBackend::GetDevice(), 1, &imageData->inFlightFences[hypatia::PresentationSystem::GetCurrentFrame()]);	
		if (vkQueueSubmit(hyp_backend::RendererBackend::GetGraphicsQueue(), 1, &submitInfo, nullptr) != VK_SUCCESS) //imageData->inFlightFences[hypatia::PresentationSystem::GetCurrentFrame()]
		{
			throw std::runtime_error("failed to submit draw command buffer!");
		}
	}

}

