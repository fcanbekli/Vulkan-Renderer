#pragma once

#include "Entity.h"

namespace hypatia
{
	class SceneGraph {
	public:
		SceneGraph(){}
		void addNewEntity(hyp_backend::Entity* entity) { m_Entities.push_back(entity); }
		hyp_backend::Entity* getEntity(std::string name);
		std::vector<hyp_backend::Entity*> m_Entities;
	private:


	};
}