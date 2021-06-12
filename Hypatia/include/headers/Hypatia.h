#pragma once
#include "PipelineDesc.h"
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
	hyp_backend::RendererBackend m_renderer;

	void Render();

	hpyStatus CreateRenderer(PIPELINE_DESC pipelineDesc);
};
}
