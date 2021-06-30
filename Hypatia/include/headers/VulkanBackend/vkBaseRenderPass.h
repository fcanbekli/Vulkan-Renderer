#pragma once
#include "VulkanBackend/vkEntity.h"
#ifdef USE_VULKAN
#include "VulkanBackend/vkData.h"
#endif

namespace hyp_vlk
{
	namespace hyp_backend {
		class BaseRenderPass {
		public:
			BaseRenderPass() {};
			void InitRenderPass();
			VkFramebuffer m_FrameBuffer;
			VkRenderPass m_Renderpass;
			void Draw();
		};
	
	}
}

