#include "VulkanBackend/vkRenderer.h"

namespace hyp_vlk
{
	namespace hyp_backend {
	
		void RendererBackend::InitRenderer()
		{
			m_computePipeline = std::make_shared<ComputePipeline>(m_pipelineDesc.computeDesc);
			m_drawPipeline = std::make_shared<DrawPipeline>(m_pipelineDesc.drawDesc);
			m_uiPipeline = std::make_shared<UIPipeline>(m_pipelineDesc.uiDesc);
			m_postPipeline = std::make_shared<PostPipeline>(m_pipelineDesc.postProcessDesc);
			
			//-------------------
			device_data.extensions = m_drawPipeline->m_drawDesc->extensions;
			window_data.hInstance = m_drawPipeline->m_drawDesc->hInstance;
			window_data.hWindow = m_drawPipeline->m_drawDesc->hwnd;
			window_data.frameBufferWidth = m_drawPipeline->m_drawDesc->frameBufferWidth;
			window_data.frameBufferHeight= m_drawPipeline->m_drawDesc->frameBufferHeight;
			//-------------------

			
			DeviceSystem::CreateInstance(&device_data);
			PresentationSystem::CreateWin32Surface(&window_data, &device_data);
			DeviceSystem::PickPhysicalDevice(&device_data);
			DeviceSystem::CreateLogicalDevice(&image_data, &device_data);
			PresentationSystem::CreateSwapChain(&device_data, &image_data, &window_data);
			PresentationSystem::CreateImageBuffer(&device_data, &image_data);
			GraphicPipelineSystem::CreateRenderPass(&device_data, &image_data);
			GraphicPipelineSystem::CreateGraphicsPipeline(&device_data, &image_data);
		}

		void RendererBackend::Render()
		{
			m_computePipeline->Exec();
			m_drawPipeline->Exec();
			m_uiPipeline->Exec();
			m_postPipeline->Exec();

			printf("FRAME DONE\n");
		}

		void RendererBackend::SyncRendererOptions(hypatia::PIPELINE_DESC pipelineDesc)
		{
			this->m_pipelineDesc = pipelineDesc;
		}
	}
}



/*


const bool enableValidationLayers = true;
const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

bool checkValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
	return VK_FALSE;
}
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
}

void hyp_vlk::hyp_backend::RendererBackend::setupDebugMessenger() {
	if (!enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	populateDebugMessengerCreateInfo(createInfo);

	if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug messenger!");
	}
}
hyp_vlk::hyp_backend::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
	hyp_vlk::hyp_backend::QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}

bool isDeviceSuitable(VkPhysicalDevice device) {
	hyp_vlk::hyp_backend::QueueFamilyIndices indices = findQueueFamilies(device);

	return indices.isComplete();
}

void hyp_vlk::hyp_backend::RendererBackend::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices) {
		if (isDeviceSuitable(device)) {
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
}

void hyp_vlk::hyp_backend::RendererBackend::initRenderer()
{
	createInstance();
	setupDebugMessenger();
	pickPhysicalDevice();
}



void hyp_vlk::hyp_backend::RendererBackend::createInstance()
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	std::vector<const char*> extensions;
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();


	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();

		populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	}
	else {
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = nullptr;
	}

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}
*/