#include "Hypatia.h"
#include <memory>
#include "GLFW/glfw3.h"
std::vector<const char*> getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	//if (enableValidationLayers) {
	//	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	//}

	return extensions;
}


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
	hypatiaRenderer->m_renderer.m_deviceManager.setExtension(getRequiredExtensions());
	while (true)
	{
		hypatiaRenderer->Render();
	}



}
