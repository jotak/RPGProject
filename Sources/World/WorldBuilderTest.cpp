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
		Character * pCharacter = new Character(*json);
		QuadData quad2(0.0f, 0.5f, 0.0f, 0.5f, string("heroe"));
		pGeometry = new GeometryQuads(&quad2, VB_Static);
		pGeometry->setOffset(CoordsScreen(280, 70));
		pCharacter->setGeometry(pGeometry);
		pCharacter->setPosition(F3DBOARD(2, 2));
		pGameObjects->push_back(pCharacter);
		_world->setActiveCharacter(pCharacter);
	}

//	string strJson("{speed:[1,6], traits:{funny:[-10,5], friendly:[-10,5], aggressive:[-10,5], charismatic:[-10,5], brave:[-10,5], charmer:[-10,5], solitary:[-10,5], tidy:[-10,5], dirty:[-10,5], cold:[-10,5], partier:[-10,5], impressionable:[-10,5], rough:[-10,5], obsequious:[-10,5], naturelover:[-10,5], malicious:[-10,5], petty:[-10,5], freeloader:[-10,5], romantic:[-10,5], coward:[-10,5], sexaddict:[-10,5], inhibited:[-10,5], impulsive:[-10,5], snob:[-10,5], technophile:[-10,5], magicphile:[-10,5], familysense:[-10,5], sly:[-10,5], taciturn:[-10,5], spitfire:[-10,5], opportunist:[-10,5], optimist:[-10,5], sceptic:[-10,5], religious:[-10,5], cartesian:[-10,5], righteous:[-10,5], egocentric:[-10,5], warm:[-10,5], leader:[-10,5], generous:[-10,5], stingy:[-10,5], faithful:[-10,5], calm:[-10,5]}}");
//	createAI(strJson, pGameObjects);
//	createAI(strJson, pGameObjects);
//	createAI(strJson, pGameObjects);
	createAI(string("{speed:[1,6], traits:{funny:3, friendly:3, charismatic:2, partier:3, freeloader:1, sexaddict:4, impulsive:1, opportunist:1, optimist:2, warm:4, leader:2}}"), pGameObjects);
	createAI(string("{speed:[1,6], traits:{aggressive:5, brave:3, rough:2, malicious:3, impulsive:3, technophile:3, spitfire:1, egocentric:4, stingy: 2}}"), pGameObjects);
	createAI(string("{speed:[1,6], traits:{brave:3, solitary:4, dirty:1, cold:1, rough:3, naturelover:2, inhibited:1, taciturn:2, sceptic:3, cartesian:3, generous: 3, calm: 4}}"), pGameObjects);

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
		AI * pAI = new AI(*json);
		delete json;
	    QuadData quad2(0.0f, 0.5f, 0.0f, 0.5f, string("heroe"));
		GeometryQuads * pGeometry = new GeometryQuads(&quad2, VB_Static);
		pGeometry->setOffset(CoordsScreen(280, 70));
		pGeometry->bindModifier(new ModColorize(Color::red));
		pGeometry->bindModifier(new ModColorize(Color::green));
		pAI->setGeometry(pGeometry);
		pAI->setPosition(F3DBOARD(2 + rand() % 2, 2 + rand() % 2));
		pAI->setBehaviour(new ErraticMoveBehaviour(pAI));
		pGameObjects->push_back(pAI);
		cout << "AI created: " << *pAI << endl;
	}
}
