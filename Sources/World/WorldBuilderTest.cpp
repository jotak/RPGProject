// -----------------------------------------------------------------
// WORLD BUILDER TEST
// Construit le monde de test
// -----------------------------------------------------------------
#include "WorldBuilderTest.h"
#include "../Managers/WorldManager.h"
#include "../Display/DisplayEngine.h"
#include "../Geometries/GeometryQuads.h"
#include "../Geometries/ModColorize.h"
#include "../AI/ErraticMoveBehaviour.h"

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
    QuadData quad(0.0f, 10.0f, 0.0f, 10.0f, string("CrackedTerrainTexture"));
    GeometryQuads * pGeometry = new GeometryQuads(&quad, VB_Static);
    pTerrain->addGeometry(pGeometry);

    Character * pCharacter = new Character(8.0f);
    QuadData quad2(0.0f, 0.5f, 0.0f, 0.5f, string("heroe"));
    pGeometry = new GeometryQuads(&quad2, VB_Static);
    pGeometry->setOffset(CoordsScreen(280, 70));
    pCharacter->setGeometry(pGeometry);
    pCharacter->setPosition(2, 2, BOARDPLANE - 0.01f);
	pGameObjects->push_back(pCharacter);
	_world->setActiveCharacter(pCharacter);

    pCharacter = new Character(3.0f);
    pGeometry = new GeometryQuads(&quad2, VB_Static);
    pGeometry->setOffset(CoordsScreen(280, 70));
    pGeometry->bindModifier(new ModColorize(Color::red));
    pGeometry->bindModifier(new ModColorize(Color::green));
    pCharacter->setGeometry(pGeometry);
    pCharacter->setPosition(5, 5, BOARDPLANE - 0.01f);
    pCharacter->setBehaviour(new ErraticMoveBehaviour(pCharacter));
	pGameObjects->push_back(pCharacter);

	_display->moveCameraTo(Coords3D(4, 4, 6));
}
