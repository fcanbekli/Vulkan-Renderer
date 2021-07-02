#pragma once
#include "FrameGraph.h"

namespace hypatia
{
	std::vector<hyp_backend::IRenderPass*> FrameGraph::m_RenderPasses;

	void FrameGraph::InitializeRenderPasses(SceneGraph* sceneGraph)
	{
		m_RenderPasses.push_back(new hyp_backend::BaseRenderPass(sceneGraph));
		
	}

	VkRenderPass FrameGraph::GetRenderPass(ERenderLayer layer)
	{
		switch (layer)
		{
		case hypatia::ERenderLayer::kBaseLayer:
			return static_cast<hyp_backend::BaseRenderPass*>(m_RenderPasses.at(0))->m_Renderpass;
			break;
		default:
			break;
		}
	}

	void FrameGraph::BuildFrame()
	{
		for(hyp_backend::IRenderPass* pass : m_RenderPasses)
		{
			pass->Draw(m_NextImageIndex);
		}
	}
}

