#pragma once
#include "pch.h"
#include "SceneGraph.h"
#include "ERenderLayer.h"
#include "VulkanBackend/vkBaseRenderPass.h"

namespace hypatia
{
	class FrameGraph
	{
	public:
		FrameGraph(){}

		void BuildFrame();
		void InitializeRenderPasses(SceneGraph* sceneGraph);
		void SetNextImage(uint32_t nextImageIndex) { this->m_NextImageIndex = nextImageIndex; }
	
		uint32_t m_NextImageIndex;
		static std::vector<hyp_backend::IRenderPass*> m_RenderPasses;	
	};
}			