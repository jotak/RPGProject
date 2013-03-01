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
	m_pPickedObject = NULL;
	m_pSpacePartition == NULL;
}

// -----------------------------------------------------------------
// Name : ~WorldManager
// -----------------------------------------------------------------
WorldManager::~WorldManager()
{
    FREE(m_pSpacePartition);
	FREEVEC(m_pGameObjects);
    _input->unsetKeyboardListener(this);
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
    _input->setKeyboardListener(this);
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
	bool eventProcessed = false;

	if (pEvent->eEvent == Event_Down
    		&& pEvent->eButton == Button1) {
		if (m_pPickedObject != NULL) {
			cout << "Clicked on " << (long)m_pPickedObject << endl;
			eventProcessed = true;
		} else if (m_pActiveCharacter != NULL) {
			Coords3D pos = _display->getBoard3D(CoordsScreen(pEvent->xPos, pEvent->yPos));
			pos.z = BOARDPLANE;
			m_pActiveCharacter->setMoveTarget(pos);
			eventProcessed = true;
		}
    } else if (pEvent->eEvent == Event_Down && pEvent->eButton == ButtonZ) {
		_display->moveCameraBy(Coords3D(0,0,-0.2));
		eventProcessed = true;
    } else if (pEvent->eEvent == Event_Down && pEvent->eButton == ButtonX) {
		_display->moveCameraBy(Coords3D(0,0,0.2));
		eventProcessed = true;
    }

    return eventProcessed;
}

// -----------------------------------------------------------------
// Name : onCursorMoveEvent
// -----------------------------------------------------------------
bool WorldManager::onCursorMoveEvent(int xPxl, int yPxl)
{
	pickObject(xPxl, yPxl);
	return true;
}

// -----------------------------------------------------------------
// Name : onKeyDown
// -----------------------------------------------------------------
bool WorldManager::onKeyDown(unsigned char key)
{
	return false;
}

// -----------------------------------------------------------------
// Name : onSpecialKeyDown
// -----------------------------------------------------------------
bool WorldManager::onSpecialKeyDown(int key)
{
	switch (key)
	{
	case SPECKEY_LEFT:
	{
		_display->moveCameraBy(Coords3D(-1,0,0));
		break;
	}
	case SPECKEY_RIGHT:
	{
		_display->moveCameraBy(Coords3D(1,0,0));
		break;
	}
	case SPECKEY_UP:
	{
		_display->moveCameraBy(Coords3D(0,1,0));
		break;
	}
	case SPECKEY_DOWN:
	{
		_display->moveCameraBy(Coords3D(0,-1,0));
		break;
	}
	}
    return false;
}

// -----------------------------------------------------------------
// Name : pickObject
// -----------------------------------------------------------------
void WorldManager::pickObject(int xPxl, int yPxl)
{
	_display->startPicking(xPxl, yPxl);
	unsigned int name = 1;
	for (GameObject* &obj : m_pGameObjects) {
		_display->pickNext(name++);
		obj->display();
	}
	unsigned int picked = _display->endPicking();
	if (picked != 0) {
		for (GameObject* &obj : m_pGameObjects) {
			picked--;
			if (picked == 0) {
				m_pPickedObject = obj;
				break;
			}
		}
	} else {
		m_pPickedObject = NULL;
	}
}
