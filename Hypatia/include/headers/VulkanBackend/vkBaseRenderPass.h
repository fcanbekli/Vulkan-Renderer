#pragma once
#include "Entity.h"
#ifdef USE_VULKAN
#include "VulkanBackend/vkData.h"
#endif

namespace hypatia
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

