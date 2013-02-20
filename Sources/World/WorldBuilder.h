#ifndef _WORLD_BUILDER_H
#define _WORLD_BUILDER_H

#include "../Utils/utils.h"
#include "Tile.h"
#include "GameObject.h"

class WorldBuilder
{
public:
	WorldBuilder() {};
    virtual ~WorldBuilder() {};

    virtual void build(vector<Tile>*, list<GameObject*>*) = 0;
};

#endif
