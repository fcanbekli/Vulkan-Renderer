#pragma once
#include "VulkanBackend/vkRenderer.h"

namespace hypatia
{
	class PresentationSystem 
	{
		friend class RendererBackend;
	public:
		PresentationSystem(){}
		void PresentFrame();
		void InitializePresentationSystem();
		void SyncRendererOptions(PIPELINE_DESC* pipelineDesc);
		static uint32_t GetNextImage();
		static size_t GetCurrentFrame() { return m_CurrentFrame;  }
		static VkSwapchainKHR GetSwapChain() { return m_SwapChain; }
		static std::vector<VkFramebuffer> GetSwapChainFrameBuffers() { return m_SwapChainFramebuffers; }
		static VkFormat GetSwapChainImageFormat() { return m_SwapChainImageFormat; }
		static VkExtent2D GetSwapChainExtent() { return m_SwapChainExtent; }
	private:
		PIPELINE_DESC* m_PipelineDesc;
		static uint32_t m_ImageIndex;
		static size_t m_CurrentFrame;
		static VkSwapchainKHR m_SwapChain;
		static std::vector<VkFramebuffer> m_SwapChainFramebuffers;
		static VkFormat m_SwapChainImageFormat;
		static VkExtent2D m_SwapChainExtent;
		std::vector<VkImage> m_SwapChainImages;
		std::vector<VkImageView> m_SwapChainImageViews;
		int m_FrameBufferWidth;
		int m_FrameBufferHeight;

		void CreateSwapChain();
		void CreateImageBuffer();
		void CreateFrameBuffer();
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	};

} 