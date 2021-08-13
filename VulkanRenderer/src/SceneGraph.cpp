#include "SceneGraph.h"

namespace hypatia
{
	Camera* SceneGraph::m_Camera;
	void SceneGraph::UpdateSceneGraph()
	{
		m_Camera->Update();
		for (int i = 0; i < m_Entities.size(); i++)
		{
			m_Entities.at(i)->Update();
		}
	}

	Entity* SceneGraph::getEntity(std::string name)
	{
		return m_Entities[0];
	}

}