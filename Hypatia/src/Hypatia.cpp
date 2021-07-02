#include "Hypatia.h"

namespace hypatia {
	void Hypatia::Render()
	{
		// Get "Next Image"
		m_FrameGraph.SetNextImage(m_PresentationSystem.GetNextImage());
		// Build Frame
		m_FrameGraph.BuildFrame();
		// Present "Next Image"
		m_PresentationSystem.PresentFrame();
	}

	hpyStatus Hypatia::InitializeRenderer(PIPELINE_DESC* pipelineDesc)
	{
		m_PipelineDesc = pipelineDesc;

		//Backend
		m_RendererBackend.SyncRendererOptions(pipelineDesc);
		m_RendererBackend.InitalizeRendererBackend();
		//Presentation
		m_PresentationSystem.SyncRendererOptions(pipelineDesc);
		m_PresentationSystem.InitializePresentationSystem();
		//Framebuffer
		m_FrameGraph.InitializeRenderPasses(&m_SceneGraph);
		//Library
		m_ResourceLibrary.LoadAssets();

		return khpySuccess;
	}

}
