#pragma once
#include "PipelineDesc.h"

namespace hyp_vlk
{
	namespace hyp_backend {
		using namespace hypatia;

		class DrawPipeline{
		public:
			DrawPipeline(std::shared_ptr<PIPELINE_DRAW_DESC> drawDesc) { this->m_drawDesc = drawDesc; }

			std::shared_ptr<PIPELINE_DRAW_DESC> m_drawDesc;

			void Exec() { printf("Draw Pipeline Worked \n"); }
		};
	}
}