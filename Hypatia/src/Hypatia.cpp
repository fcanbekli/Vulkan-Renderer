#include "Hypatia.h"

namespace hypatia {
	void Hypatia::Render()
	{
		// Get "Next Image"
		
		// Build Frame

		// Present "Next Image"
	}

	hpyStatus Hypatia::InitializeRenderer(PIPELINE_DESC pipelineDesc)
	{
		//SceneGraph

		//Framebuffer
		m_FrameGraph.BindSceneGraph(&m_SceneGraph);
		//Library
		m_ResourceLibrary.LoadAssets();
		//Backend
		m_RendererBackend.SyncRendererOptions(pipelineDesc);
		return khpySuccess;
	}

}
