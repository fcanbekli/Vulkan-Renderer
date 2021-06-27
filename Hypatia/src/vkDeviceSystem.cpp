#include "VulkanBackend/vkDeviceSystem.h"



namespace hyp_vlk
{
	namespace hyp_backend {
		

		bool DeviceSystem::checkDeviceExtensionSupport(VkPhysicalDevice device) {
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

		
		void DeviceSystem::CreateInstance(DeviceData* deviceData)
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

			//TODO:() Refactor extensions
			createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceData->extensions.size());
			createInfo.ppEnabledExtensionNames = deviceData->extensions.data();
			createInfo.enabledLayerCount = 0;
			createInfo.pNext = nullptr;
			
			if (vkCreateInstance(&createInfo, nullptr, &deviceData->instance) != VK_SUCCESS) {
				throw std::runtime_error("failed to create instance!");
			}
		}

		void DeviceSystem::PickPhysicalDevice(DeviceData *deviceData)
		{
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(deviceData->instance, &deviceCount, nullptr);

			if (deviceCount == 0) {
				throw std::runtime_error("failed to find GPUs with Vulkan support!");
			}

			std::vector<VkPhysicalDevice> devices(deviceCount);
			vkEnumeratePhysicalDevices(deviceData->instance, &deviceCount, devices.data());

			for (const auto& device : devices) {
				if (isDeviceSuitable(device)) {
					deviceData->physicalDevice = device;
					break;
				}
			}

			if (deviceData->physicalDevice == VK_NULL_HANDLE) {
				throw std::runtime_error("failed to find a suitable GPU!");
			}

			VkPhysicalDeviceProperties physicalDeviceProperties;
			vkGetPhysicalDeviceProperties(
				deviceData->physicalDevice,
				&physicalDeviceProperties
			);
		
			VkPhysicalDeviceFeatures physicalDeviceFeatures;
			vkGetPhysicalDeviceFeatures(
				deviceData->physicalDevice,
				&physicalDeviceFeatures
			);

			VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
			vkGetPhysicalDeviceMemoryProperties(
				deviceData->physicalDevice,
				&physicalDeviceMemoryProperties
			);
		}

		void DeviceSystem::CreateLogicalDevice(ImageData *imageData, DeviceData *deviceData)
		{
			QueueFamilyIndices indices = findQueueFamilies(deviceData->physicalDevice);

			std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
			std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

			float queuePriority = 1.0f;
			for (uint32_t queueFamily : uniqueQueueFamilies) {
				VkDeviceQueueCreateInfo queueCreateInfo{};
				queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueCreateInfo.queueFamilyIndex = queueFamily;
				queueCreateInfo.queueCount = 1;
				queueCreateInfo.pQueuePriorities = &queuePriority;
				queueCreateInfos.push_back(queueCreateInfo);
			}

			VkDeviceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
			createInfo.pQueueCreateInfos = queueCreateInfos.data();
			createInfo.pEnabledFeatures = &deviceData->physicalDeviceFeatures;
			createInfo.enabledExtensionCount = static_cast<uint32_t>(imageData->deviceExtensions.size());
			createInfo.ppEnabledExtensionNames = imageData->deviceExtensions.data();

// 			if (enableValidationLayers) {
// 				createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
// 				createInfo.ppEnabledLayerNames = validationLayers.data();
// 			}
// 			else {
// 				createInfo.enabledLayerCount = 0;
// 			}

			if (vkCreateDevice(deviceData->physicalDevice, &createInfo, nullptr, &deviceData->device) != VK_SUCCESS) {
				throw std::runtime_error("failed to create logical device!");
			}

			vkGetDeviceQueue(deviceData->device, indices.graphicsFamily.value(), 0, &deviceData->graphicsQueue);
			vkGetDeviceQueue(deviceData->device, indices.presentFamily.value(), 0, &deviceData->presentQueue);

		}

		bool DeviceSystem::isDeviceSuitable(VkPhysicalDevice device)
		{
			QueueFamilyIndices indices = findQueueFamilies(device);

			bool extensionsSupported = checkDeviceExtensionSupport(device);

			bool swapChainAdequate = false;
			if (extensionsSupported) {
				SwapChainSupportDetails swapChainSupport = PresentationSystem::querySwapChainSupport(device);
				swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
			}

			return indices.isComplete() && extensionsSupported && swapChainAdequate;
		}

		
		//WindowData->Surface
		QueueFamilyIndices DeviceSystem::findQueueFamilies(VkPhysicalDevice device) {
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
				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, window_data.surface, &presentSupport); //To determine whether a queue family of a physical device supports presentation to a given surface

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
	}
}
