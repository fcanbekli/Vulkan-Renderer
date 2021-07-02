#pragma once
#include "Entity.h"

namespace hypatia
{
	class SceneGraph {
	public:
		SceneGraph(){}

		void addNewEntity(Entity* entity) { m_Entities.push_back(entity); }
		Entity* getEntity(std::string name);

		std::vector<Entity*> m_Entities;
	};
}