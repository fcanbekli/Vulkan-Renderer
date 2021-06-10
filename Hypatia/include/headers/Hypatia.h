#pragma once
#include <stdio.h>
#include "PipelineDesc.h"
#include "Base.h"
#include <hpyStatus.h>
#define USE_VULKAN = 1

#ifdef USE_GL
#include "GLApp.h"
using namespace alita_gl;
#endif

#ifdef USE_VULKAN
#include "VulkanBackend/vkRenderer.h"
using namespace hyp_vlk;
#endif




namespace hypatia {
	class Hypatia {
public:
	Hypatia() {};
	hyp_backend::RendererBackend renderer;

	void render();

	hpyStatus createRenderer(PIPELINE_COMPUTE_DESC* computeDesc, PIPELINE_DRAW_DESC* drawDesc, PIPELINE_POSTPROCESS_DESC* postProcessDecs, PIPELINE_UI_DESC* uiDesc);
};
}
