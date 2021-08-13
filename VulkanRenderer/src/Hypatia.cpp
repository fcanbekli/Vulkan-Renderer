#include "Hypatia.h"

namespace hypatia {
	void Hypatia::Render()
	{
		// Get "Next Image"
		m_FrameGraph.SetNextImage(m_PresentationSystem.GetNextImage());
		// Build Frame
		m_FrameGraph.BuildFrame();
		m_FrameGraph.SubmitFrame();
		// Present "Next Image"
		m_PresentationSystem.PresentFrame();
	}

	hpyStatus Hypatia::InitializeRenderer(RENDERER_DESC* pipelineDesc)
	{
		m_PipelineDesc = pipelineDesc;

		//Backend
		m_RendererBackend.SyncRendererOptions(pipelineDesc);
		m_RendererBackend.InitalizeRendererBackend();
		//Presentation
		m_PresentationSystem.SyncRendererOptions(pipelineDesc);
		m_PresentationSystem.InitializePresentationSystem();
		//Render Passes
		m_FrameGraph.m_SceneGraph = &m_SceneGraph;
		m_FrameGraph.InitializeRenderPasses();
		//Framebuffer
		m_PresentationSystem.CreateFrameBuffer();
		//Library
		m_ResourceLibrary.LoadAssets();



		return khpySuccess;
	}

}
