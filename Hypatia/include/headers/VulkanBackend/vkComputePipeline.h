#pragma once
#include "PipelineDesc.h"

namespace hypatia
{
	namespace hyp_backend {
		using namespace hypatia;

		class ComputePipeline{
		public:
			ComputePipeline(std::shared_ptr<PIPELINE_COMPUTE_DESC> computeDesc) { this->m_computeDesc = computeDesc; }

			std::shared_ptr<PIPELINE_COMPUTE_DESC> m_computeDesc;

			void Exec() { printf("Compute Pipeline Worked \n");}
		};
	}
}