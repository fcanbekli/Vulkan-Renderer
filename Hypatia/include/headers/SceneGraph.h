#pragma once
#include "pch.h"
#ifdef USE_VULKAN
#include "VulkanBackend/vkEntity.h"
using namespace hyp_vlk::hyp_backend;
#endif

namespace hypatia
{
	class SceneGraph {
	public:
		SceneGraph() {};
		void addNewEntity(Entity entity) { entities.push_back(&entity); }
		//inline Entity getEntity(std::string name) { return entities[name]; }
		static std::vector<Entity*> GetEntities(ERenderLayer layer) { return entities; };
		static std::vector<Entity*> entities;
	};
}