#include "Hypatia.h"


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
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hypatia", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	hypatia::Hypatia* hypatiaRenderer = new hypatia::Hypatia();
	hypatia::hpyStatus status;

	auto computeDesc = std::make_shared<hypatia::PIPELINE_COMPUTE_DESC>();
	auto drawDesc = std::make_shared<hypatia::PIPELINE_DRAW_DESC>();
	auto uiDesc = std::make_shared<hypatia::PIPELINE_UI_DESC>();
	auto postProcessDesc = std::make_shared<hypatia::PIPELINE_POSTPROCESS_DESC>();

	hyp_vlk::hyp_backend::device_data.extensions = getRequiredExtensions();

	drawDesc->hwnd = glfwGetWin32Window(window);
	drawDesc->hInstance = GetModuleHandle(nullptr);
	drawDesc->extensions = getRequiredExtensions();
	glfwGetFramebufferSize(window, &drawDesc->frameBufferWidth, &drawDesc->frameBufferHeight);

	hypatia::PIPELINE_DESC pipelineDesc = {};
	pipelineDesc.drawDesc = drawDesc;
	pipelineDesc.computeDesc = computeDesc;
	pipelineDesc.uiDesc = uiDesc;
	pipelineDesc.postProcessDesc = postProcessDesc;
	status = hypatiaRenderer->CreateRenderer(pipelineDesc);
	
	hypatiaRenderer->m_renderer.InitRenderer();

	hyp_vlk::hyp_backend::Entity* entity = new hyp_vlk::hyp_backend::Entity("Test Entity");
	hypatiaRenderer->m_renderer.m_SceneGraph.addNewEntity(entity);

	
	while (true)
	{
		hypatiaRenderer->Render();

		glfwPollEvents();
	}

}
