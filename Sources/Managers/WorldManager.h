#ifndef _WORLD_MANAGER_H
#define _WORLD_MANAGER_H

#include "../World/WorldBuilder.h"
#include "../World/Character.h"
#include "../Input/EventListener.h"
#include "../Input/KeyboardListener.h"

class WorldManager : public EventListener, public KeyboardListener
{
public:
    ~WorldManager();
    static WorldManager * getInstance()
    {
        if (m_pInstance == NULL) m_pInstance = new WorldManager();
        return m_pInstance;
    };

    // Init / Update / Display
    void init(WorldBuilder * pBuilder);
    void update(double delta);
    void display();

    // Input functions
    bool onCatchButtonEvent(ButtonAction * pEvent);
    bool onCursorMoveEvent(int xPxl, int yPxl);
    virtual bool onKeyDown(unsigned char c);
    virtual bool onSpecialKeyDown(int key);

    Character * getActiveCharacter() { return m_pActiveCharacter; };
    void setActiveCharacter(Character * c) { m_pActiveCharacter = c; };

private:
    WorldManager();
    static WorldManager * m_pInstance;

    Terrain m_Terrain;
    list<GameObject*> m_pGameObjects;
    Character * m_pActiveCharacter;
};

// Helper alias
#define _world WorldManager::getInstance()

#endif
