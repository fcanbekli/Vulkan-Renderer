#pragma once
#include "VulkanBackend/vkValidationLayerManager.h"
#include "VulkanBackend/vkData.h"
#include "VulkanBackend/vkPresentationManager.h"
namespace hyp_vlk
{
	namespace hyp_backend {

		//TODO:(Caner, Fatih) Separate Queue Logic



		class DeviceSystem {
		private:
			friend class PresentationSystem;
			//Queues
			//ValidationLayer
			static bool isDeviceSuitable(VkPhysicalDevice device);
			static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

			static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		public:
			DeviceSystem(){}
			static void CreateInstance(VkInstance &instance, std::vector<const char*>& extensions);
			static void PickPhysicalDevice(VkInstance &instance, VkPhysicalDevice &physicalDevice);
			static void CreateLogicalDevice(VkPhysicalDevice& physicalDevice, VkDevice& device, VkQueue& graphicsQueue, VkQueue& presentQueue, std::vector<const char*> &deviceExtensions);
			
		};
	}
}