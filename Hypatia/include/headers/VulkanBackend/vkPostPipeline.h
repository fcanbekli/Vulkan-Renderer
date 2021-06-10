#pragma once
#include "VulkanBackend/vkIPipeline.h"

namespace hyp_vlk
{
	namespace hyp_backend {
		class PostPipeline : public IPipeline {
		public:
			PostPipeline(hypatia::PIPELINE_POSTPROCESS_DESC* postProcessDesc) { this->postProcessDesc = postProcessDesc; }
			hypatia::PIPELINE_POSTPROCESS_DESC* postProcessDesc;
			void exec() override { printf("Post Pipeline Worked \n"); }
		};
	}
}