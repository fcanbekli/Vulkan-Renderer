#pragma once
#include "ResourceLibrary.h"

namespace hypatia
{

	void ResourceLibrary::LoadAssets()
	{
		LoadShaders();
		CreateMaterials();
	}

	void ResourceLibrary::LoadShaders()
	{
		m_Shaders.push_back(new hyp_backend::Shader("../../Hypatia/res/shaders/vertex_shader.spv", "../../Hypatia/res/shaders/fragment_shader.spv"));
	}

	void ResourceLibrary::CreateMaterials()
	{
		m_Materials.push_back(new Material(m_Shaders.at(0)));
	}
}