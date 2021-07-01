#pragma once
#include "VulkanBackend/vkComputePipeline.h"
#include "VulkanBackend/vkUIPipeline.h"
#include "VulkanBackend/vkPostPipeline.h"
#include "VulkanBackend/vkDrawPipeline.h"

#include "VulkanBackend/vkValidationLayerManager.h"

#include "VulkanBackend/vkGraphicPipelineSystem.h"


#include "SceneGraph.h"
#include "PipelineDesc.h"

namespace hypatia
{
	namespace hyp_backend {

		struct QueueFamilyIndices 
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;

			bool isComplete() {
				return graphicsFamily.has_value() && presentFamily.has_value();
			}
		};

		struct SwapChainSupportDetails 
		{
			VkSurfaceCapabilitiesKHR capabilities; //Basic surface capabilities (min/max number of images in swap chain, min/max width and height of images)
			std::vector<VkSurfaceFormatKHR> formats; //Surface formats (pixel format, color space)
			std::vector<VkPresentModeKHR> presentModes; //Available presentation modes
		};

		class RendererBackend {
			friend class PresentationSystem;
		public:
			RendererBackend() {};
			void InitalizeRendererBackend();
			void SyncRendererOptions(hypatia::PIPELINE_DESC pipelineDesc);


			static VkDevice GetDevice() { return m_Device; }
			static VkQueue GetGraphicsQueue() { return m_GraphicsQueue; }
			static VkQueue GetPresentQueue() { return m_PresentQueue; }
			static VkPhysicalDevice GetPhysicalDevice() { return m_PhysicalDevice; }
			static SwapChainSupportDetails GetSwapChainSupportDetails() { return m_SwapChainSupportDetails; }
			static VkSurfaceKHR GetSurface() { return m_Surface; }


			static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		private:
			void IntializeInstance();
			void IntializePhysicalDevice();
			void IntializeDevice();


			bool IsDeviceSuitable(VkPhysicalDevice device);

			bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
			void CreateWin32Surface();
			SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);


			VkInstance m_Instance;
			static VkPhysicalDevice m_PhysicalDevice;
			VkPhysicalDeviceProperties physicalDeviceProperties;
			VkPhysicalDeviceFeatures physicalDeviceFeatures;
			VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
			static VkDevice m_Device;
			static VkQueue m_GraphicsQueue;
			static VkQueue m_PresentQueue;
			std::vector<const char*> m_Extensions;
			std::vector<const char*> m_DeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
			static VkSurfaceKHR m_Surface;
			static SwapChainSupportDetails m_SwapChainSupportDetails;



			std::shared_ptr<DrawPipeline> m_drawPipeline;
			std::shared_ptr<UIPipeline> m_uiPipeline;
			std::shared_ptr<ComputePipeline> m_computePipeline;
			std::shared_ptr<PostPipeline> m_postPipeline;

			hypatia::PIPELINE_DESC m_pipelineDesc;
		};
	}
}

