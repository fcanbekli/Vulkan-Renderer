#pragma once
#include "VulkanBackend/vkBaseRenderPass.h"
#include <VulkanBackend/vkData.h>
using namespace hyp_vlk::hyp_backend;
#include "pch.h"


#include "SceneGraph.h"
namespace hyp_vlk
{
	namespace hyp_backend {
		class FrameGraph
		{
		public:
			BaseRenderPass m_BaseRenderPass;
			uint32_t m_NextImageIndex;
			hypatia::SceneGraph* m_SceneGraph;
			void setNextImage(uint32_t nextImageIndex) { this->m_NextImageIndex = nextImageIndex; }
			VkFramebuffer BuildFrame(DeviceData* deviceData, ImageData* imageData);
			void SetupSceneGraph(hypatia::SceneGraph* sceneGraph) { m_SceneGraph = sceneGraph; }
		};
	}
}