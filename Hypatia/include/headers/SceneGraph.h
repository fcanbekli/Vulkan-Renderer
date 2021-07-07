#pragma once
#include "Entity.h"
#include "Camera.h"
namespace hypatia
{
	class SceneGraph {
	public:
		SceneGraph(){}

		void addNewEntity(Entity* entity) { m_Entities.push_back(entity); }
		void UpdateSceneGraph();
		Entity* getEntity(std::string name);
		Camera m_Camera;
		std::vector<Entity*> m_Entities;
	};
}