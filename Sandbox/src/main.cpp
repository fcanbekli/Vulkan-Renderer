#include "Hypatia.h"
#include <memory>

int main()
{
	hypatia::Hypatia* hypatiaRenderer = new hypatia::Hypatia();
	hypatia::hpyStatus status;

	std::shared_ptr<hypatia::PIPELINE_COMPUTE_DESC> computeDesc;
	std::shared_ptr<hypatia::PIPELINE_DRAW_DESC> drawDesc;
	std::shared_ptr<hypatia::PIPELINE_UI_DESC> uiDesc;
	std::shared_ptr<hypatia::PIPELINE_POSTPROCESS_DESC> postProcessDesc;

	hypatia::PIPELINE_DESC pipelineDesc = {};

	pipelineDesc.drawDesc = drawDesc;
	pipelineDesc.computeDesc = computeDesc;
	pipelineDesc.uiDesc = uiDesc;
	pipelineDesc.postProcessDesc = postProcessDesc;


	status = hypatiaRenderer->CreateRenderer(pipelineDesc);
	hypatiaRenderer->m_renderer.InitRenderer();
	while (true)
	{
		hypatiaRenderer->Render();
	}



}

