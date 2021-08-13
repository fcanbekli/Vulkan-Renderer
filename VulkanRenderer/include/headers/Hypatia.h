#pragma once
#include "VulkanBackend/vkRenderer.h"
#include "PresentationSystem.h"
#include "PipelineDesc.h"
#include <hpyStatus.h>
#include "ResourceLibrary.h"
#include "FrameGraph.h"

namespace hypatia {
	class Hypatia {
public:
	Hypatia() {};

	hpyStatus InitializeRenderer(RENDERER_DESC* pipelineDesc);
	void Render();
	ResourceLibrary GetResourceLibrary() { return m_ResourceLibrary; };
	SceneGraph& GetSceneGraph() { return m_SceneGraph; };
private:
	hyp_backend::RendererBackend m_RendererBackend;
	SceneGraph m_SceneGraph;

	FrameGraph m_FrameGraph;
	ResourceLibrary m_ResourceLibrary;
	PresentationSystem m_PresentationSystem;	

	RENDERER_DESC* m_PipelineDesc;
};
}
