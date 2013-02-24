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

    Character * pCharacter = new Character(8.0f);
    QuadData quad2(0.0f, 10.0f, 0.0f, 10.0f, string("heroe"));
    pGeometry = new GeometryQuads(&quad2, VB_Static);
    pGeometry->setOffset(CoordsScreen(280, 350));
    pCharacter->setGeometry(pGeometry);
    pCharacter->setPosition(25, 30, BOARDPLANE - 0.01f);
	pGameObjects->push_back(pCharacter);
	_world->setActiveCharacter(pCharacter);

	_display->moveCameraTo(Coords3D(50, 50, 98));
}
