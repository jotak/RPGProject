// -----------------------------------------------------------------
// WORLD BUILDER TEST
// Construit le monde de test
// -----------------------------------------------------------------
#include "WorldBuilderTest.h"
#include "../Managers/WorldManager.h"
#include "../Display/DisplayEngine.h"
#include "../Geometries/GeometryQuads.h"

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
void WorldBuilderTest::build(Terrain * pTerrain, list<GameObject*> * pGameObjects)
{
    QuadData quad(0.0f, 128.0f, 0.0f, 128.0f, string("CrackedTerrainTexture"));
    GeometryQuads * pGeometry = new GeometryQuads(&quad, VB_Static);
    pTerrain->addGeometry(pGeometry);

    Character * pObj = new Character(5.0f);
    QuadData quad2(0.0f, 10.0f, 0.0f, 10.0f, string("heroe"));
    pGeometry = new GeometryQuads(&quad2, VB_Static);
    pObj->setGeometry(pGeometry);
    pObj->setPosition(15, 15);
	pGameObjects->push_back(pObj);
	_world->setActiveCharacter(pObj);

	_display->moveCameraTo(Coords3D(50, 50, 98));
}
