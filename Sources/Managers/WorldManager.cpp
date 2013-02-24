// -----------------------------------------------------------------
// WORLD MANAGER
// Gere le monde
// -----------------------------------------------------------------
#include "WorldManager.h"
#include "../Input/InputEngine.h"

WorldManager * WorldManager::m_pInstance = NULL;

// -----------------------------------------------------------------
// Name : WorldManager
// -----------------------------------------------------------------
WorldManager::WorldManager() : EventListener(4)
{
	m_pActiveCharacter = NULL;
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
    _input->addCursoredEventListener(this);
    _input->pushUncursoredEventListener(this);
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void WorldManager::update(double delta)
{
	for (GameObject* &obj : m_pGameObjects) {
		obj->update(delta);
	}
}

// -----------------------------------------------------------------
// Name : display
// -----------------------------------------------------------------
void WorldManager::display()
{
	m_Terrain.display();
	for (GameObject* &obj : m_pGameObjects) {
		obj->display();
	}
}

// -----------------------------------------------------------------
// Name : onCatchButtonEvent
//  Called by Input Engine.
//  Must return true if event is consumed ; false to let the event be catched by other modules
//  Transfer the message to top frame under mouse
// -----------------------------------------------------------------
bool WorldManager::onCatchButtonEvent(ButtonAction * pEvent)
{
    if (m_pActiveCharacter != NULL
    		&& pEvent->eEvent == Event_Down
    		&& pEvent->eButton == Button1) {
        Coords3D pos = _display->get3DCoords(CoordsScreen(pEvent->xPos, pEvent->yPos, BOARDPLANE), DMS_3D);
        pos.z = BOARDPLANE;
        m_pActiveCharacter->setMoveTarget(pos);
    	return true;
    }

    return false;
}

// -----------------------------------------------------------------
// Name : onCursorMoveEvent
// -----------------------------------------------------------------
bool WorldManager::onCursorMoveEvent(int xPxl, int yPxl)
{
	return true;
}
