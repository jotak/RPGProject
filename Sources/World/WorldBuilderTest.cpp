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
#include "../AI/AI.h"
#include "../Managers/DebugManager.h"

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
    pTerrain->setDimensions(0, 10, 0, 10);

	string sError;
	JoSon * json = JoSon::fromString(string("{speed:3, traits:{friendly:2, funny:1}}"), &sError);
	if (json == NULL) {
		_debug->notifyErrorMessage(sError);
	} else {
		Character * pCharacter = new Character(json);
		QuadData quad2(0.0f, 0.5f, 0.0f, 0.5f, string("heroe"));
		pGeometry = new GeometryQuads(&quad2, VB_Static);
		pGeometry->setOffset(CoordsScreen(280, 70));
		pCharacter->setGeometry(pGeometry);
		pCharacter->setPosition(F3DBOARD(2, 2));
		pGameObjects->push_back(pCharacter);
		_world->setActiveCharacter(pCharacter);
	}

	createAI(string("{speed:[1,6], traits:{friendly:[-5,5], funny:[-5,5]}}"), pGameObjects);
	createAI(string("{speed:[1,6], traits:{friendly:[-5,5], funny:[-5,5]}}"), pGameObjects);
	createAI(string("{speed:[1,6], traits:{friendly:[-5,5], funny:[-5,5]}}"), pGameObjects);
	createAI(string("{speed:[1,6], traits:{friendly:[-5,5], funny:[-5,5]}}"), pGameObjects);
	createAI(string("{speed:[1,6], traits:{friendly:[-5,5], funny:[-5,5]}}"), pGameObjects);

	_display->moveCameraTo(f3d(4, 4, 6));
}

// -----------------------------------------------------------------
// Name : createAI
// -----------------------------------------------------------------
void WorldBuilderTest::createAI(string strJson, list<GameObject*> * pGameObjects)
{
	string sError;
	JoSon * json = JoSon::fromString(strJson, &sError);
	if (json == NULL) {
		_debug->notifyErrorMessage(string("Error when loading json: ") + strJson + " - Error message: " + sError);
	} else {
		AI * pAI = new AI(json);
		delete json;
	    QuadData quad2(0.0f, 0.5f, 0.0f, 0.5f, string("heroe"));
		GeometryQuads * pGeometry = new GeometryQuads(&quad2, VB_Static);
		pGeometry->setOffset(CoordsScreen(280, 70));
		pGeometry->bindModifier(new ModColorize(Color::red));
		pGeometry->bindModifier(new ModColorize(Color::green));
		pAI->setGeometry(pGeometry);
		pAI->setPosition(F3DBOARD(rand() % 10, rand() % 10));
		pAI->setBehaviour(new ErraticMoveBehaviour(pAI));
		pGameObjects->push_back(pAI);
		cout << "AI created: " << *pAI << endl;
	}
}
