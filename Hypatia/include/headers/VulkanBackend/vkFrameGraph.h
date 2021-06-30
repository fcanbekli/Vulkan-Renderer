#pragma once
#include "VulkanBackend/vkBaseRenderPass.h"
#include <VulkanBackend/vkData.h>
using namespace hyp_vlk::hyp_backend;
#include "pch.h"

namespace hypatia
{
	class FrameGraph
	{
	public:
		BaseRenderPass m_BaseRenderPass;
		uint32_t m_NextImageIndex;
		void setNextImage(uint32_t nextImageIndex) { this->m_NextImageIndex = nextImageIndex; }
		VkFramebuffer BuildFrame(DeviceData* deviceData, ImageData* imageData);
	};
}
