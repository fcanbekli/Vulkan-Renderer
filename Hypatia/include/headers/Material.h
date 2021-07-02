#pragma once
#include "pch.h"
#include "VulkanBackend/vkShader.h"

namespace hypatia {
	class Material {
	public:
		Material(hyp_backend::Shader* shader);
		hyp_backend::Shader* m_Shader;
		
	};
}

