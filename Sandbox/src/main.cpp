#include "Hypatia.h"
int main()
{
	hypatia::Hypatia* hypatiaRenderer = new hypatia::Hypatia();
	hypatia::hpyStatus status;

	hypatia::PIPELINE_COMPUTE_DESC computeDesc = {};
	hypatia::PIPELINE_DRAW_DESC drawDesc = {};
	hypatia::PIPELINE_POSTPROCESS_DESC postProcessDesc = {};
	hypatia::PIPELINE_UI_DESC uiDesc = {};

	status = hypatiaRenderer->createRenderer(&computeDesc, &drawDesc, &postProcessDesc, &uiDesc);
	hypatiaRenderer->renderer.initRenderer();
	while (true)
	{
		hypatiaRenderer->render();
	}



}

