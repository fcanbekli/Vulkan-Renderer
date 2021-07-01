#include "VulkanBackend/vkRenderer.h"

namespace hypatia
{
	namespace hyp_backend {
	
		void RendererBackend::InitalizeRendererBackend()
		{
// 			m_computePipeline = std::make_shared<ComputePipeline>(m_pipelineDesc.computeDesc);
// 			m_drawPipeline = std::make_shared<DrawPipeline>(m_pipelineDesc.drawDesc);
// 			m_uiPipeline = std::make_shared<UIPipeline>(m_pipelineDesc.uiDesc);
// 			m_postPipeline = std::make_shared<PostPipeline>(m_pipelineDesc.postProcessDesc);
// 			
// 			//-------------------
// 			device_data.extensions = m_drawPipeline->m_drawDesc->extensions;
// 			window_data.hInstance = m_drawPipeline->m_drawDesc->hInstance;
// 			window_data.hWindow = m_drawPipeline->m_drawDesc->hwnd;
// 			window_data.frameBufferWidth = m_drawPipeline->m_drawDesc->frameBufferWidth;
// 			window_data.frameBufferHeight= m_drawPipeline->m_drawDesc->frameBufferHeight;
// 			//-------------------
// 
// 				
// 			DeviceSystem::CreateInstance(&device_data);
// 			PresentationSystem::CreateWin32Surface(&window_data, &device_data);
// 			DeviceSystem::PickPhysicalDevice(&device_data);
// 			DeviceSystem::CreateLogicalDevice(&image_data, &device_data);
// 			
// 			PresentationSystem::CreateSwapChain(&device_data, &image_data, &window_data);
// 		
// 			PresentationSystem::CreateImageBuffer(&device_data, &image_data);
// 			GraphicPipelineSystem::CreateRenderPass(&device_data, &image_data);
// 			GraphicPipelineSystem::CreateGraphicsPipeline(&device_data, &image_data);
// 			PresentationSystem::CreateFrameBuffer(&device_data, &image_data);
// 			PresentationSystem::CreateCommandPool(&device_data, &image_data);
// 			PresentationSystem::CreateCommandBuffer(&device_data, &image_data);
// 			PresentationSystem::CreateSyncObjects(&device_data, &image_data);
// 			m_FrameGraph.SetupSceneGraph(&m_SceneGraph);
// 			m_FrameGraph.m_BaseRenderPass.InitRenderPass();
		}


		void RendererBackend::SyncRendererOptions(hypatia::PIPELINE_DESC pipelineDesc)
		{
			this->m_pipelineDesc = pipelineDesc;
		}



		void RendererBackend::IntializeInstance()
		{
			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Hypatia Engine";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "Hypatia";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			VkInstanceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
			createInfo.ppEnabledExtensionNames = extensions.data();
			createInfo.enabledLayerCount = 0;
			createInfo.pNext = nullptr;

			if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
				throw std::runtime_error("failed to create instance!");
			}

		}

		void RendererBackend::IntializePhysicalDevice()
		{
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

			if (deviceCount == 0) {
				throw std::runtime_error("failed to find GPUs with Vulkan support!");
			}

			std::vector<VkPhysicalDevice> devices(deviceCount);
			vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

			for (const auto& device : devices) {
				if (IsDeviceSuitable(device)) {
					m_PhysicalDevice = device;
					break;
				}
			}

			if (m_PhysicalDevice == VK_NULL_HANDLE) {
				throw std::runtime_error("failed to find a suitable GPU!");
			}

			VkPhysicalDeviceProperties physicalDeviceProperties;
			vkGetPhysicalDeviceProperties(
				m_PhysicalDevice,
				&physicalDeviceProperties
			);

			VkPhysicalDeviceFeatures physicalDeviceFeatures;
			vkGetPhysicalDeviceFeatures(
				m_PhysicalDevice,
				&physicalDeviceFeatures
			);

			VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
			vkGetPhysicalDeviceMemoryProperties(
				m_PhysicalDevice,
				&physicalDeviceMemoryProperties
			);
		}

		bool RendererBackend::IsDeviceSuitable(VkPhysicalDevice device)
		{
			QueueFamilyIndices indices = FindQueueFamilies(device);

			bool extensionsSupported = CheckDeviceExtensionSupport(device);

			bool swapChainAdequate = false;
			if (extensionsSupported) {
				SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
				swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
			}

			return indices.isComplete() && extensionsSupported && swapChainAdequate;
		}


		QueueFamilyIndices RendererBackend::FindQueueFamilies(VkPhysicalDevice device)
		{
			QueueFamilyIndices indices;

			uint32_t queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

			std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

			int i = 0;
			for (const auto& queueFamily : queueFamilies) {
				if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
					indices.graphicsFamily = i;
				}

				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport); //To determine whether a queue family of a physical device supports presentation to a given surface

				if (presentSupport) {
					indices.presentFamily = i;
				}

				if (indices.isComplete()) {
					break;
				}

				i++;
			}

			return indices;
		}


		bool RendererBackend::CheckDeviceExtensionSupport(VkPhysicalDevice device)
		{
			uint32_t extensionCount;
			vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

			std::vector<VkExtensionProperties> availableExtensions(extensionCount);
			vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

			std::set<std::string> requiredExtensions(image_data.deviceExtensions.begin(), image_data.deviceExtensions.end());

			for (const auto& extension : availableExtensions) {
				requiredExtensions.erase(extension.extensionName);
			}

			return requiredExtensions.empty();
		}

		void RendererBackend::CreateWin32Surface()
		{
			VkWin32SurfaceCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			createInfo.hwnd = m_pipelineDesc.drawDesc->hwnd;
			createInfo.hinstance = m_pipelineDesc.drawDesc->hInstance;

			if (vkCreateWin32SurfaceKHR(m_Instance, &createInfo, NULL, &m_Surface) != VK_SUCCESS) {
				throw std::runtime_error("failed to create window surface!");
			}
		}

		SwapChainSupportDetails RendererBackend::QuerySwapChainSupport(VkPhysicalDevice device)
		{
			SwapChainSupportDetails details;

			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &details.capabilities);

			uint32_t formatCount;
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, nullptr);

			if (formatCount != 0) {
				details.formats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, details.formats.data());
			}

			uint32_t presentModeCount;
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, nullptr);

			if (presentModeCount != 0) {
				details.presentModes.resize(presentModeCount);
				vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, details.presentModes.data());
			}
			m_SwapChainSupportDetails = details;
			return details;
		}

	}
}
