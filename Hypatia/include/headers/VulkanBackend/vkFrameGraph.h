#pragma once
#include "VulkanBackend/vkRenderPass.h"

namespace hyp_vlk
{
	namespace hyp_backend {
		class FrameGraph
		{
		public:
			FrameGraph();
			RenderPass m_BaseRenderPass;

			void BuildFrame();

		};
	}
}
