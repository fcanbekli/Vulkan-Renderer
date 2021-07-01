#pragma once
#include "Entity.h"
#include "vkIRenderPass.h"
#include "vkRenderer.h"
#include "PresentationSystem.h"

namespace hypatia
{
	namespace hyp_backend {
		class BaseRenderPass : public IRenderPass {
		public:
			BaseRenderPass(SceneGraph* _sceneGraph);
			SceneGraph* m_SceneGraph;
			void InitRenderPass() override;
			VkFramebuffer m_FrameBuffer;
			VkRenderPass m_Renderpass;
			//image
			//image view
			void Draw(uint32_t nextImageIndex);
		};
	}
}

