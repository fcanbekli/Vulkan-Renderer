#pragma once
#include "VulkanBackend/vkIPipeline.h"
namespace hyp_vlk
{
	namespace hyp_backend {
		class UIPipeline : public IPipeline {
		public:
			UIPipeline(hypatia::PIPELINE_UI_DESC* uiDesc) { this->uiDesc = uiDesc; }
			hypatia::PIPELINE_UI_DESC* uiDesc;
			void exec() override { printf("UI Pipeline Worked \n"); };
		};
	}
}