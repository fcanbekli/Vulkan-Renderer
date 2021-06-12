#pragma once
#include "PipelineDesc.h"
namespace hyp_vlk
{
	namespace hyp_backend {
		using namespace hypatia;

		class PostPipeline{
		public:
			PostPipeline(std::shared_ptr<PIPELINE_POSTPROCESS_DESC> postProcessDesc) { this->m_postProcessDesc = postProcessDesc; }

			std::shared_ptr<PIPELINE_POSTPROCESS_DESC> m_postProcessDesc;

			void Exec() { printf("Post Pipeline Worked \n"); }
		};
	}
}