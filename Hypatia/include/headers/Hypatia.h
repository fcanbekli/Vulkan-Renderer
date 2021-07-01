#pragma once
#include "PipelineDesc.h"
#include "ResourceLibrary.h"
#include "FrameGraph.h"
#include "PresentationSystem.h"
#include <hpyStatus.h>
#include "VulkanBackend/vkData.h"

#define USE_VULKAN = 1

#ifdef USE_VULKAN
#include "VulkanBackend/vkRenderer.h"
#endif




namespace hypatia {
	class Hypatia {
public:
	Hypatia() {};

	void Render();

	SceneGraph m_SceneGraph;
	hyp_backend::RendererBackend m_RendererBackend;
	FrameGraph m_FrameGraph;
	ResourceLibrary m_ResourceLibrary;
	PresentationSystem m_PresentationSystem;


	hpyStatus InitializeRenderer(PIPELINE_DESC pipelineDesc);
};
}
