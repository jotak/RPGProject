// -----------------------------------------------------------------
// AI
// -----------------------------------------------------------------
#include "AI.h"
#include "../Managers/WorldManager.h"
#include "../Managers/DebugManager.h"
#include "../Physics/SpacePart.h"

JoSon * AI::m_pTraitsRelations = NULL;

// -----------------------------------------------------------------
// Name : AI
// -----------------------------------------------------------------
AI::AI(JoS_Element& json) : Character(json)
{
	m_pBehaviour = NULL;
	m_fInteractTimer = 0;
}

// -----------------------------------------------------------------
// Name : ~AI
// -----------------------------------------------------------------
AI::~AI()
{
	FREE(m_pBehaviour);
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void AI::update(double delta)
{
	m_fInteractTimer -= delta;
	if (m_fInteractTimer <= 0) {
		m_fInteractTimer = INTERACT_DELAY;
		list<PartitionableItem*> * lstSurroundingObjects = _world->getSpacePartition()->getDirectNeighbours(this);
		checkInteractions(lstSurroundingObjects);
		for (int i = 0; i < NB_INDIRECT_NEIGHBOURS_ZONES; i++) {
			lstSurroundingObjects = _world->getSpacePartition()->getIndirectNeighbours(this, i);
			checkInteractions(lstSurroundingObjects);
		}
	}

	if (m_pBehaviour != NULL) {
		m_pBehaviour->update(delta);
	}
	Character::update(delta);
}

// -----------------------------------------------------------------
// Name : checkInteractions
// -----------------------------------------------------------------
void AI::checkInteractions(list<PartitionableItem*> * lstSurroundingObjects)
{
	if (lstSurroundingObjects != NULL) {
		for (PartitionableItem * pItem : *lstSurroundingObjects) {
			if (pItem != this) {
				// Skip "this" since the AI itself is in the list
				f3d vec = getPosition() - pItem->getPosition();
				if (vec.getsize() < AI_INTERACTION_RADIUS) {
					interact((GameObject*) pItem);
				}
			}
		}
	}
}

// -----------------------------------------------------------------
// Name : interact
// -----------------------------------------------------------------
void AI::interact(GameObject * pOther)
{
	if (pOther->isCharacter()) {
		float f = computeObjectiveAttraction((Character*) pOther);
		cout << "interaction [" << *this << ", " << *(Character*) pOther << "] :" << f << endl;
	}
}

// -----------------------------------------------------------------
// Name : computeObjectiveAttraction
// -----------------------------------------------------------------
float AI::computeObjectiveAttraction(Character * pOther)
{
	// TODO: bad algorithm ; impact of relation should not be the same when "from" is high, and when "from" is low. Division by nbRelations is bad.
	float attraction = 0.0f;
	int nbRelations = 0;
	long_hash * pThisTraits = getTraits();
	long_hash * pOtherTraits = pOther->getTraits();
	for (pair<string, long> from : *pThisTraits) {
		for (pair<string, long> to : *pOtherTraits) {
			// fRelation [-1,1]
			float fRelation = (float)from.second/*[0,5]*/ * (float)to.second/*[0,5]*/ * getTraitsRelation(from.first, to.first)/*[0,1]*/ / (float)(TRAIT_MAX_VALUE * TRAIT_MAX_VALUE);
			// Square it so that an "extreme" relation counts for more than a neutral one
			attraction += (fRelation * abs(fRelation));
			nbRelations++;
		}
	}
	if (nbRelations > 0) {
		attraction /= (float) nbRelations;
	}

	// "Friendly" traits automatically improves attraction
//	int friendly = (*pThisTraits)[TRAITS_FRIENDLY];
//	if (friendly > 0) {
//		attraction = (attraction + friendly) / (friendly+1);
//	}

	return attraction;
}

// -----------------------------------------------------------------
// Name : initData
//	static
// -----------------------------------------------------------------
void AI::initData()
{
    // Build file name
    string jsonDesc = string(AI_PATH) + "traitsRelations.json";
    string err;
    m_pTraitsRelations = JoSon::fromFile(jsonDesc, &err);
    if (m_pTraitsRelations == NULL) {
    	_debug->notifyErrorMessage(err);
    }
}

// -----------------------------------------------------------------
// Name : releaseData
//	static
// -----------------------------------------------------------------
void AI::releaseData()
{
	FREE(m_pTraitsRelations);
}

// -----------------------------------------------------------------
// Name : getTraitsRelation
// Relation is not comutable: getTraitsRelation(A, B) != getTraitsRelation(B, A)
//	static
// -----------------------------------------------------------------
float AI::getTraitsRelation(string from, string towards)
{
	if (m_pTraitsRelations != NULL && !(*m_pTraitsRelations)[from][towards].isNull()) {
		float value = (float) (*m_pTraitsRelations)[from][towards].toDouble();
		// Cap value in [-1,1]
		if (value > 1.0f) {
			value = 1.0f;
		} else if (value < -1.0f) {
			value = -1.0f;
		}
		return value;
	}
	// Value not found => neutral relation
	return 0.0f;
}
