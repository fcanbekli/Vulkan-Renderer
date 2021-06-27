#pragma once
#include "ERenderLayer.h"
#include "VulkanBackend/vkBufferFactory.h"
#include "Material.h"

namespace hyp_vlk
{
	namespace hyp_backend {
		class Entity {
		public:
			Entity();
			VkCommandBuffer m_CommandBuffer;
			hypatia::ERenderLayer m_RenderLayer;
			hypatia::Material m_Material;
		};
	}
} 