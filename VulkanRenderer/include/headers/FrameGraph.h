#pragma once
#include "pch.h"
#include "SceneGraph.h"
#include "ERenderLayer.h"
#include "VulkanBackend/vkRenderer.h"

namespace hypatia
{
	class FrameGraph
	{
	public:
		FrameGraph(){}
		
		void BuildFrame();
		void SubmitFrame();
		void InitializeRenderPasses();
		void SetNextImage(uint32_t nextImageIndex) { this->m_NextImageIndex = nextImageIndex; }
	
		uint32_t m_NextImageIndex;
		hypatia::SceneGraph* m_SceneGraph;	
	};
}			