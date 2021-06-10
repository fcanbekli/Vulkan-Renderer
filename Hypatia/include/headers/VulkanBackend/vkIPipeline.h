#pragma once
#include "VulkanBackend/vkBase.h"
#include "PipelineDesc.h"
namespace hyp_vlk
{
	namespace hyp_backend {
		class IPipeline {
			virtual void exec() = 0;

		};
	}
}