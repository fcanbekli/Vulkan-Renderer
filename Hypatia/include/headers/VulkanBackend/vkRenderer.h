#pragma once
#include "VulkanBackend/vkComputePipeline.h"
#include "VulkanBackend/vkUIPipeline.h"
#include "VulkanBackend/vkPostPipeline.h"
#include "VulkanBackend/vkDrawPipeline.h"
#include "VulkanBackend/vkDeviceManager.h"
#include "PipelineDesc.h"

namespace hyp_vlk
{
	namespace hyp_backend {

		class RendererBackend {
		public:
			RendererBackend() {};
			void InitRenderer();
			void Render();
			void SyncRendererOptions(hypatia::PIPELINE_DESC pipelineDesc);

			std::shared_ptr<DrawPipeline> m_drawPipeline;
			std::shared_ptr<UIPipeline> m_uiPipeline;
			std::shared_ptr<ComputePipeline> m_computePipeline;
			std::shared_ptr<PostPipeline> m_postPipeline;

			DeviceManager m_deviceManager;

			hypatia::PIPELINE_DESC m_pipelineDesc;

		};
	}
}

