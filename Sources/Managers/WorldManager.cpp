// -----------------------------------------------------------------
// WORLD MANAGER
// Gere le monde
// -----------------------------------------------------------------
#include "WorldManager.h"

WorldManager * WorldManager::m_pInstance = NULL;

// -----------------------------------------------------------------
// Name : WorldManager
// -----------------------------------------------------------------
WorldManager::WorldManager()
{
}

// -----------------------------------------------------------------
// Name : ~WorldManager
// -----------------------------------------------------------------
WorldManager::~WorldManager()
{
	FREEVEC(m_pGameObjects);
}

// -----------------------------------------------------------------
// Name : init
// -----------------------------------------------------------------
void WorldManager::init(WorldBuilder * pBuilder)
{
	pBuilder->build(&m_Terrain, &m_pGameObjects);
	delete pBuilder;
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void WorldManager::update(double delta)
{
	for (list<GameObject*>::iterator it = m_pGameObjects.begin(); it != m_pGameObjects.end(); ++it) {
		(*it)->update(delta);
	}
}

// -----------------------------------------------------------------
// Name : display
// -----------------------------------------------------------------
void WorldManager::display()
{
	m_Terrain.display();
	for (list<GameObject*>::iterator it = m_pGameObjects.begin(); it != m_pGameObjects.end(); ++it) {
		(*it)->display();
	}
}
