#pragma once
#include "PipelineDesc.h"

namespace hyp_vlk
{
	namespace hyp_backend {
		using namespace hypatia;
		class UIPipeline{
		public:
			UIPipeline(std::shared_ptr<PIPELINE_UI_DESC> uiDesc) { this->m_uiDesc = uiDesc; }

			std::shared_ptr<PIPELINE_UI_DESC> m_uiDesc;

			void Exec() { printf("UI Pipeline Worked \n"); };
		};
	}
}