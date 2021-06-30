#pragma once
#include "VulkanBackend/vkValidationLayerManager.h"
#include "VulkanBackend/vkData.h"
#include "VulkanBackend/vkPresentationSystem.h"
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
			static void CreateInstance(DeviceData* deviceData);
			static void PickPhysicalDevice(DeviceData *deviceData);
			static void CreateLogicalDevice(ImageData* imageData, DeviceData* deviceData);
			
		};
	}
}