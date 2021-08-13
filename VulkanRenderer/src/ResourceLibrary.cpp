#pragma once
#include "ResourceLibrary.h"

namespace hypatia
{

	void ResourceLibrary::LoadAssets()
	{
		LoadShaders();
		LoadModels();
		CreateMaterials();
	}

	void ResourceLibrary::LoadShaders()
	{
		m_Shaders.push_back(new hyp_backend::Shader("../../VulkanRenderer/res/shaders/vertex_shader.spv", "../../VulkanRenderer/res/shaders/fragment_shader.spv"));
	}

	void ResourceLibrary::LoadModels()
	{
		m_Models.push_back(new hyp_backend::Model());
	}

	void ResourceLibrary::CreateMaterials()
	{
		m_Materials.push_back(new Material(m_Shaders.at(0)));
	}
}