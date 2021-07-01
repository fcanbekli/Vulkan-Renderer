#pragma once
#include "FrameGraph.h"

namespace hypatia
{
	void FrameGraph::InitializeRenderPasses(SceneGraph* sceneGraph)
	{
		m_RenderPasses.push_back(new BaseRenderPass(sceneGraph));
		
	}

	VkRenderPass FrameGraph::GetRenderPass(ERenderLayer layer)
	{
		switch (layer)
		{
		case hypatia::ERenderLayer::kBaseLayer:
			return static_cast<BaseRenderPass*>(m_RenderPasses.at(0))->m_Renderpass;
			break;
		default:
			break;
		}
	}

	void FrameGraph::BuildFrame()
	{
		for(IRenderPass* pass : m_RenderPasses) 
		{
			pass->Draw(m_NextImageIndex);
		}
	}
}

