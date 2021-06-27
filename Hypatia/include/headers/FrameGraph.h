#pragma once
#include "RenderPass.h"

namespace hypatia
{
	class FrameGraph
	{
		BaseRenderPass m_BaseRenderPass;

		void BuildFrame();
	};
}
