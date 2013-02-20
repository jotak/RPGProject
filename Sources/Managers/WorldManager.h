#ifndef _WORLD_MANAGER_H
#define _WORLD_MANAGER_H

#include "../World/WorldBuilder.h"

class WorldManager
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

private:
    WorldManager();
    static WorldManager * m_pInstance;

    vector<Tile> m_Tiles;
    list<GameObject*> m_pGameObjects;
};

// Helper alias
#define _world WorldManager::getInstance()

#endif
