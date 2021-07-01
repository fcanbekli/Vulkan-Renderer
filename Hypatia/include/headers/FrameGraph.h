#pragma once
#include "VulkanBackend/vkBaseRenderPass.h"
#include <VulkanBackend/vkData.h>
using namespace hypatia::hyp_backend;
#include "pch.h"


#include "SceneGraph.h"
#include <ERenderLayer.h>
namespace hypatia
{
	class FrameGraph
	{
	public:
		uint32_t m_NextImageIndex;

		static std::vector<IRenderPass*> m_RenderPasses;

		void SetNextImage(uint32_t nextImageIndex) { this->m_NextImageIndex = nextImageIndex; }
		static VkRenderPass GetRenderPass(ERenderLayer layer);
		void BuildFrame();
		void InitializeRenderPasses(SceneGraph* sceneGraph);
		void BindSceneGraph(SceneGraph* sceneGraph) { m_SceneGraph = sceneGraph; }
	};
}

		
				