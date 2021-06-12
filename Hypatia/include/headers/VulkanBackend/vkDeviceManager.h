#pragma once
#include <vulkan/vulkan_core.h>
#include "VulkanBackend/vkValidationLayerManager.h"
#include <stdexcept>
#include <optional>
#include <vector>
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


		class DeviceManager {
		private:
			//Vulkan Instance
			VkInstance m_instance;

			//Devices
			VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
			VkDevice m_device;

			//Queues
			VkQueue m_graphicsQueue;

			//ValidationLayer
			ValidationLayerManager m_validationManager;

			void CreateInstance();
			void PickPhysicalDevice();
			void CreateLogicalDevice();
			bool isDeviceSuitable(VkPhysicalDevice device);
			QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		public:
			DeviceManager(){}
			VkPhysicalDevice GetPhysicalDevice() { return m_physicalDevice; }
			VkDevice GetLogicalDevice() { return m_device; }

			void CreateDevice();

		};
	}
}