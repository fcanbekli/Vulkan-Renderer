#pragma once
#include "Entity.h"
#include "Camera.h"
namespace hypatia
{
	class Entity;
	class SceneGraph {
	public:
		SceneGraph(){}

		void addNewEntity(Entity* entity) { m_Entities.push_back(entity); }
		void UpdateSceneGraph();
		static Camera* GetCamera() { return m_Camera; }
		Entity* getEntity(std::string name);
		static Camera* m_Camera;
		std::vector<Entity*> m_Entities;
	};
}