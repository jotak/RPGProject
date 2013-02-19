// -----------------------------------------------------------------
// WORLD MANAGER
// Gere le monde
// -----------------------------------------------------------------
#include "WorldManager.h"

#include "../World/MovingObject.h"

WorldManager * WorldManager::m_pInstance = NULL;

// -----------------------------------------------------------------
// Name : WorldManager
// -----------------------------------------------------------------
WorldManager::WorldManager()
{
	for (int i = 0; i < 64; i++) {
		m_Tiles.push_back(Tile(i%8, i/8));
	}
	MovingObject * pObj = new MovingObject();
	pObj->setX(2);
	pObj->setY(2);
	m_pGameObjects.push_back(pObj);
	pObj = new MovingObject();
	pObj->setX(3);
	pObj->setY(3);
	m_pGameObjects.push_back(pObj);
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
void WorldManager::init()
{
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void WorldManager::update(double delta)
{
}

// -----------------------------------------------------------------
// Name : display
// -----------------------------------------------------------------
void WorldManager::display()
{
}
