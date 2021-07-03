#pragma once
#include "VulkanBackend/vkShader.h"
#include "Material.h"

namespace hypatia
{
	class ResourceLibrary {
	public:
		ResourceLibrary(){}

		void LoadAssets();
		void LoadShaders();
		void CreateMaterials();

		std::vector<Material*> m_Materials;
		std::vector<hyp_backend::Shader*> m_Shaders;
	};
}