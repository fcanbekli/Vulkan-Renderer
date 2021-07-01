#pragma once
#include "VulkanBackend/vkBaseRenderPass.h"
#include <VulkanBackend/vkData.h>
using namespace hypatia::hyp_backend;
#include "pch.h"


#include "SceneGraph.h"
namespace hypatia
{
	class FrameGraph
	{
	public:
		BaseRenderPass m_BaseRenderPass;

		uint32_t m_NextImageIndex;

		SceneGraph* m_SceneGraph;

		void setNextImage(uint32_t nextImageIndex) { this->m_NextImageIndex = nextImageIndex; }
		VkFramebuffer BuildFrame(DeviceData* deviceData, ImageData* imageData);
		void BindSceneGraph(SceneGraph* sceneGraph) { m_SceneGraph = sceneGraph; }
	};
}