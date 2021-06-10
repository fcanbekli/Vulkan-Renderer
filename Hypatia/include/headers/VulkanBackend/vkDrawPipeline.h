#pragma once
#include "VulkanBackend/vkIPipeline.h"
namespace hyp_vlk
{
	namespace hyp_backend {
		class DrawPipeline : public IPipeline {
		public:
			DrawPipeline(hypatia::PIPELINE_DRAW_DESC* drawDesc) { this->drawDesc = drawDesc; }
			hypatia::PIPELINE_DRAW_DESC* drawDesc;

			void exec() override {
				printf("Draw Pipeline Worked \n");
			}
		};
	}
}