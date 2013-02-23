// -----------------------------------------------------------------
// WORLD BUILDER TEST
// Construit le monde de test
// -----------------------------------------------------------------
#include "WorldBuilderTest.h"
#include "../World/MovingObject.h"
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

    MovingObject * pObj = new MovingObject();
	pObj->setX(2);
	pObj->setY(2);
	pGameObjects->push_back(pObj);
	pObj = new MovingObject();
	pObj->setX(3);
	pObj->setY(3);
	pGameObjects->push_back(pObj);

	_display->moveCameraTo(Coords3D(50, 50, 98));
}
