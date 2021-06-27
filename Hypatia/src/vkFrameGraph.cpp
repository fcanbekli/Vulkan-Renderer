#pragma once
#include "VulkanBackend/vkFrameGraph.h"

namespace hyp_vlk
{
	namespace hyp_backend
	{
		FrameGraph::FrameGraph()
		{
			
		}

		void FrameGraph::BuildFrame()
		{
			m_BaseRenderPass.Draw();
		}

	}
}