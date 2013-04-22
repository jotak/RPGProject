// -----------------------------------------------------------------
// FISHING ACTION
// -----------------------------------------------------------------
#include "FishingAction.h"
#include "../AI.h"
#include "../../Managers/WorldManager.h"
#include "../../World/Terrain.h"
#include "../../World/FinalObjects/Trout.h"
#include "../../World/FinalObjects/Carp.h"

#define MAX_WAIT_TIME			300 // 5 min
#define FISHING_MIN_ABILITY		1
#define FISHING_MAX_ABILITY		4

// -----------------------------------------------------------------
// Name : FishingAction
// -----------------------------------------------------------------
FishingAction::FishingAction(AI * ai, const JoS_Element& json) : AIAction(ai)
{
	// Find nearest water point
	const list<WaterArea*>& areas = _world->getTerrain()->getWaterAreas();
	pFishingArea = NULL;
	double nearestDistance = -1;
	for (WaterArea * pArea : areas) {
		point_and_distance distance = pArea->getArea()->closestDistanceTo(m_pAI->getPosition());
		if (nearestDistance == -1 || nearestDistance > get<1>(distance)) {
			pFishingArea = pArea;
			nearestDistance = get<1>(distance);
			// TODO: store nearest point too
		}
	}
	int ability = JSonUtil::getCappedInt(json["ability"], FISHING_MIN_ABILITY, FISHING_MAX_ABILITY, FISHING_MIN_ABILITY);
	abilityModifier = (double) ability / 2.0f; // from 0.5 to 2
	m_fWait = 0;
}

// -----------------------------------------------------------------
// Name : ~FishingAction
// -----------------------------------------------------------------
FishingAction::~FishingAction()
{
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void FishingAction::update(double delta)
{
	m_fWait -= delta;
	if (m_fWait < 0) {
		fish();
	} else if (pFishingArea != NULL) {
		// Does it bit?
		double treshold = delta * 60.0f * abilityModifier * pFishingArea->getFishingProbability();
		if (100.0f * rand() / RAND_MAX < treshold) {
			// Yes!
			FoodObject * pFish = NULL;
			int rnd = (int) FRAND100(100);
			if (rnd < pFishingArea->getTroutsPct()) {
				pFish = new Trout();
			} else {
				pFish = new Carp();
			}
			m_pAI->addToInventory(pFish);
			fish();
		}
	}
}

// -----------------------------------------------------------------
// Name : fish
// -----------------------------------------------------------------
void FishingAction::fish()
{
	m_fWait = MAX_WAIT_TIME;
	if (pFishingArea == NULL) {
		m_pAI->say("There's no water around!");
	} else {
		// TODO: Move a bit around
	}
}
