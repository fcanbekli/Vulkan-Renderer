#pragma once
#include "pch.h"
#ifdef USE_VULKAN
#include "VulkanBackend/vkShader.h"
using namespace hyp_vlk::hyp_backend;
#endif

namespace hypatia
{
	class Material {
	public:
		Material() {};
		Shader m_Shader;
	};
}