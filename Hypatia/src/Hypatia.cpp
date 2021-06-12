#include "Hypatia.h"

namespace hypatia {
	void Hypatia::Render()
	{
		m_renderer.Render();
	}

	hpyStatus Hypatia::CreateRenderer(PIPELINE_DESC pipelineDesc)
	{
		m_renderer.SyncRendererOptions(pipelineDesc);
		return khpySuccess;
	}

}
