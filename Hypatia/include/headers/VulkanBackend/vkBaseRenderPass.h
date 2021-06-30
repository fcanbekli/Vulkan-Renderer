#pragma once
#include "VulkanBackend/vkEntity.h"
#ifdef USE_VULKAN
#include "vkData.h"
#endif
namespace hypatia
{
	class BaseRenderPass {
	public:
		VkFramebuffer m_FrameBuffer;
		VkRenderPass m_Renderpass;
		void Draw();
	};


}
