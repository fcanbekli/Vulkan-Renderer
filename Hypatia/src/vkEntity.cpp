#pragma once
#include "VulkanBackend/vkEntity.h"

namespace hyp_vlk
{
	namespace hyp_backend {
		
		Entity::Entity()
		{
			BufferFactory::CreateCommandBuffer(m_CommandBuffer);
		}

	}
}