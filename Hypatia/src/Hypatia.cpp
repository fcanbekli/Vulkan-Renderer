#include "Hypatia.h"

namespace hypatia {
	void Hypatia::render()
	{
		renderer.render();
	}

	hpyStatus Hypatia::createRenderer(PIPELINE_COMPUTE_DESC* computeDesc, PIPELINE_DRAW_DESC* drawDesc, PIPELINE_POSTPROCESS_DESC* postProcessDecs, PIPELINE_UI_DESC* uiDesc)
	{
		renderer.syncRendererOptions(computeDesc, drawDesc, postProcessDecs, uiDesc);
		if (renderer.computeDesc == nullptr) {
			return hpyError;
		}
		return hpySuccess;
	}

}
