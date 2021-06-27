#pragma once
#include "VulkanBackend/vkComputePipeline.h"
#include "VulkanBackend/vkUIPipeline.h"
#include "VulkanBackend/vkPostPipeline.h"
#include "VulkanBackend/vkDrawPipeline.h"
#include "VulkanBackend/vkDeviceSystem.h"
#include "VulkanBackend/vkValidationLayerManager.h"
#include "VulkanBackend/vkPresentationSystem.h"
#include "VulkanBackend/vkGraphicPipelineSystem.h"
#include "VulkanBackend/vkData.h"
#include "PipelineDesc.h"
#include "vkFrameGraph.h"

namespace hyp_vlk
{
	namespace hyp_backend {

		class RendererBackend {
		public:
			RendererBackend() {};
			void InitRenderer();
			void Render();
			void SyncRendererOptions(hypatia::PIPELINE_DESC pipelineDesc);

			
		private:
			FrameGraph m_FrameGraph;
			std::shared_ptr<DrawPipeline> m_drawPipeline;
			std::shared_ptr<UIPipeline> m_uiPipeline;
			std::shared_ptr<ComputePipeline> m_computePipeline;
			std::shared_ptr<PostPipeline> m_postPipeline;

			ValidationLayerManager m_validationManager;
			PresentationSystem m_presentationManager;

			hypatia::PIPELINE_DESC m_pipelineDesc;
		};
	}
}

