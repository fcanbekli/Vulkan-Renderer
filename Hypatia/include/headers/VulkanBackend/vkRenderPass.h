#pragma once
#include "vkEntity.h"
#ifdef USE_VULKAN
#include "vkData.h"
#endif
#include "SceneGraph.h"
#include "ERenderLayer.h"

namespace hyp_vlk
{
	namespace hyp_backend {
		class RenderPass {
		private:
			VkImageView m_ImageView;
			VkImage m_Image;
			VkFramebuffer m_Framebuffer;
		public:
			RenderPass() {};
			void InitializeRenderPass();
			static VkRenderPass m_RenderPass;
			static VkRenderPass GetRenderPass() { return m_RenderPass; };
			void CreateImageBuffer();
			void InitializeFrameBuffer();
			void Draw();
		};
	}
}
