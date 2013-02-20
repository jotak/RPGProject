// -----------------------------------------------------------------
// WORLD BUILDER TEST
// Construit le monde de test
// -----------------------------------------------------------------
#include "WorldBuilderTest.h"

#include "../World/MovingObject.h"

// -----------------------------------------------------------------
// Name : WorldBuilderTest
// -----------------------------------------------------------------
WorldBuilderTest::WorldBuilderTest()
{
}

// -----------------------------------------------------------------
// Name : ~WorldBuilderTest
// -----------------------------------------------------------------
WorldBuilderTest::~WorldBuilderTest()
{
}

// -----------------------------------------------------------------
// Name : init
// -----------------------------------------------------------------
void WorldBuilderTest::build(vector<Tile> * pTiles, list<GameObject*> * pGameObjects)
{
	for (int i = 0; i < 64; i++) {
		pTiles->push_back(Tile(i%8, i/8));
	}
	MovingObject * pObj = new MovingObject();
	pObj->setX(2);
	pObj->setY(2);
	pGameObjects->push_back(pObj);
	pObj = new MovingObject();
	pObj->setX(3);
	pObj->setY(3);
	pGameObjects->push_back(pObj);
}
