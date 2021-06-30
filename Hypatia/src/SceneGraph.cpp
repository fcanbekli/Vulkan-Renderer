#include "SceneGraph.h"

namespace hypatia
{
	
	hyp_backend::Entity* SceneGraph::getEntity(std::string name)
	{
		return m_Entities[0];
	}

}