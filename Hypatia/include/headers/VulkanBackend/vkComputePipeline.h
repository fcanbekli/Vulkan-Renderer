#pragma once
#include "VulkanBackend/vkIPipeline.h"

namespace hyp_vlk
{
	namespace hyp_backend {

		class ComputePipeline : public IPipeline {
		public:
			ComputePipeline(hypatia::PIPELINE_COMPUTE_DESC* computeDesc) { this->computeDesc = computeDesc; }
			hypatia::PIPELINE_COMPUTE_DESC* computeDesc;
			void exec() override { printf("Compute Pipeline Worked \n");}
		};
	}
}