#pragma once
#include "pch.h"
#include "VulkanBackend/vkData.h"

namespace hyp_vlk
{
	namespace hyp_backend {

		class BufferFactory {
		public:
			static void CreateCommandBuffer(VkCommandBuffer& buffer);
		};
	}
}




