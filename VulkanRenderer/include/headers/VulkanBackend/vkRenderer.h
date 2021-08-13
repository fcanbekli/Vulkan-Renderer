#pragma once
#include "VulkanBackend/vkComputePipeline.h"
#include "VulkanBackend/vkUIPipeline.h"
#include "VulkanBackend/vkPostPipeline.h"
#include "VulkanBackend/vkDrawPipeline.h"
#include <VulkanBackend/vkRenderPass.h>
#include <ERenderLayer.h>

namespace hyp_backend
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete()
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities; //Basic surface capabilities (min/max number of images in swap chain, min/max width and height of images)
		std::vector<VkSurfaceFormatKHR> formats; //Surface formats (pixel format, color space)
		std::vector<VkPresentModeKHR> presentModes; //Available presentation modes
	};

	class RendererBackend
	{
		friend class PresentationSystem;
	public:
		RendererBackend() {};
		void InitalizeRendererBackend();
		void SyncRendererOptions(hypatia::RENDERER_DESC* pipelineDesc);

		static VkInstance GetInstance() { return m_Instance; }
		static VkDevice GetDevice() { return m_Device; }
		static VkPhysicalDevice GetPhysicalDevice() { return m_PhysicalDevice; }
		static VkQueue GetGraphicsQueue() { return m_GraphicsQueue; }
		static VkQueue GetPresentQueue() { return m_PresentQueue; }
		static VkRenderPass GetRenderLayer(ERenderLayer renderLayer);

		static VkSurfaceKHR GetSurface() { return m_Surface; }
		static VkCommandPool GetCommandPool() { return m_CommandPool; };
		static std::vector<VkCommandBuffer> GetCommandBuffers() { return m_CommandBuffers; };
		static SwapChainSupportDetails GetSwapChainSupportDetails() { return m_SwapChainSupportDetails; }
		static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		static RenderLayers m_RenderLayers;


		static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	private:
		void IntializeInstance();
		void IntializePhysicalDevice();
		void IntializeDevice();
		void InitializeCommandPool();
		void InitializeCommandBuffer();
		void CreateWin32Surface();

		bool IsDeviceSuitable(VkPhysicalDevice device);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

		static VkInstance m_Instance;
		static VkDevice m_Device;
		static VkPhysicalDevice m_PhysicalDevice;
		static VkCommandPool m_CommandPool;
		static std::vector<VkCommandBuffer> m_CommandBuffers;
		static VkQueue m_GraphicsQueue;
		static VkQueue m_PresentQueue;
		static VkSurfaceKHR m_Surface;
		static SwapChainSupportDetails m_SwapChainSupportDetails;

		VkPhysicalDeviceProperties m_PhysicalDeviceProperties;
		VkPhysicalDeviceFeatures m_PhysicalDeviceFeatures;
		VkPhysicalDeviceMemoryProperties m_PhysicalDeviceMemoryProperties;
		std::vector<const char*> m_Extensions;
		std::vector<const char*> m_DeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		std::shared_ptr<DrawPipeline> m_drawPipeline;
		std::shared_ptr<UIPipeline> m_uiPipeline;
		std::shared_ptr<ComputePipeline> m_computePipeline;
		std::shared_ptr<PostPipeline> m_postPipeline;

		hypatia::RENDERER_DESC* m_PipelineDesc;
	};
}
