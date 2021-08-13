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

	hypatia::RENDERER_DESC pipelineDesc = {};
	pipelineDesc.hwnd = glfwGetWin32Window(window);
	pipelineDesc.hInstance = GetModuleHandle(nullptr);
	pipelineDesc.extensions = getRequiredExtensions();
	glfwGetFramebufferSize(window, &pipelineDesc.frameBufferWidth, &pipelineDesc.frameBufferHeight);

	hypatiaRenderer->InitializeRenderer(&pipelineDesc);

	hypatia::Entity* entity = new hypatia::Entity();
	entity->m_Material = hypatiaRenderer->GetResourceLibrary().m_Materials.at(0);
	entity->m_Model = hypatiaRenderer->GetResourceLibrary().m_Models.at(0);
	hypatiaRenderer->GetSceneGraph().addNewEntity(entity);

	hypatia::Camera* camera = new hypatia::Camera();
	hypatiaRenderer->GetSceneGraph().m_Camera = camera;

	while (true)
	{
		hypatiaRenderer->GetSceneGraph().UpdateSceneGraph();
		hypatiaRenderer->Render();
		glfwWaitEvents();
		glfwPollEvents();

	}

}
