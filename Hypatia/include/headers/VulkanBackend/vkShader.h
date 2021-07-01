#pragma once
#include "pch.h"
#include "FrameGraph.h"

namespace hypatia{
	namespace hyp_backend {

		class Shader {
		public:
			Shader(const std::string& vertexPath, const std::string& fragmentPath) {}
			VkPipeline m_Pipeline;
		};
	}
}
