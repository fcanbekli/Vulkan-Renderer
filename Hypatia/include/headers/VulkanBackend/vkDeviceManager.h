#pragma once
#include "VulkanBackend/vkValidationLayerManager.h"

namespace hyp_vlk
{
	namespace hyp_backend {

		//TODO:(Caner, Fatih) Separate Queue Logic
		struct QueueFamilyIndices {
			std::optional<uint32_t> graphicsFamily;

			bool isComplete() {
				return graphicsFamily.has_value();
			}
		};


		class DeviceSystem {
		private:
			//Queues
			//ValidationLayer

			static bool isDeviceSuitable(VkPhysicalDevice device);
			static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		public:
			DeviceSystem(){}
			static void CreateInstance(VkInstance &instance, std::vector<const char*>& extensions);
			static void PickPhysicalDevice(VkInstance &instance, VkPhysicalDevice &physicalDevice);
			static void CreateLogicalDevice(VkPhysicalDevice& physicalDevice, VkDevice& device, VkQueue& graphicsQueue);
			
		};
	}
}