#pragma once
#include "FrameGraph.h"

namespace hypatia
{
	std::vector<hyp_backend::IRenderPass*> FrameGraph::m_RenderPasses;

	void FrameGraph::InitializeRenderPasses(SceneGraph* sceneGraph)
	{
		m_RenderPasses.push_back(new hyp_backend::BaseRenderPass(sceneGraph));
		
	}

	void FrameGraph::BuildFrame()
	{
		for(hyp_backend::IRenderPass* pass : m_RenderPasses)
		{
			pass->Draw(m_NextImageIndex);
		}
	}
}

