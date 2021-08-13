#pragma once
#include "Entity.h"
#include "vkIRenderPass.h"
#include "vkRenderer.h"
#include "PresentationSystem.h"
#include "SceneGraph.h"
#include "vkRenderPass.h"

namespace hyp_backend {
	class BaseRenderPass : public IRenderPass {
	public:
		BaseRenderPass(hypatia::SceneGraph* _sceneGraph);
		hypatia::SceneGraph* m_SceneGraph;
		void InitRenderPass() override;
		//image
		//image view
		void Draw(uint32_t nextImageIndex) override;
	};
}
