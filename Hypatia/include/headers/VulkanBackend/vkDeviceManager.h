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
			VkQueue m_graphicsQueue;
			//ValidationLayer
			ValidationLayerManager m_validationManager;

			bool isDeviceSuitable(VkPhysicalDevice device);
			QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		public:
			DeviceSystem(){}
			void CreateInstance(VkInstance &instance, std::vector<const char*>& extensions);
			void PickPhysicalDevice(VkInstance &instance, VkPhysicalDevice &physicalDevice);
			void CreateLogicalDevice(VkPhysicalDevice &physicalDevice, VkDevice &device);
			
		};
	}
}