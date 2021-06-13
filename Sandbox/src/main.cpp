#include "Hypatia.h"

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

	drawDesc->hwnd = glfwGetWin32Window(window);
	drawDesc->hInstance = GetModuleHandle(nullptr);

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
