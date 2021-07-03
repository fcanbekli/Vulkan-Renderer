#pragma once
#include "VulkanBackend/vkShader.h"
#include "VulkanBackend/vkModel.h"
#include "Material.h"

namespace hypatia
{
	class ResourceLibrary {
	public:
		ResourceLibrary(){}

		void LoadAssets();
		void LoadShaders();
		void LoadModels();
		void CreateMaterials();


		std::vector<Material*> m_Materials;
		std::vector<hyp_backend::Model*> m_Models;
		std::vector<hyp_backend::Shader*> m_Shaders;
	};
}