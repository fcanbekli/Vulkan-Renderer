#pragma once
#include "VulkanBackend/vkEntity.h"

namespace hypatia
{
	class SceneGraph {
	public:
		SceneGraph(){}
		void addNewEntity(Entity entity) { entities.push_back(&entity); }
		void getEntity(std::string name){}

	private:
		std::vector<Entity*> entities;

	};
}