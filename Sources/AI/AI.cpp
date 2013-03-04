// -----------------------------------------------------------------
// AI
// -----------------------------------------------------------------
#include "AI.h"
#include "../Managers/WorldManager.h"
#include "../Physics/SpacePart.h"

// -----------------------------------------------------------------
// Name : AI
// -----------------------------------------------------------------
AI::AI(JoS_Element * json) : Character(json)
{
	m_pBehaviour = NULL;
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
	list<PartitionableItem*> * lstSurroundingObjects = _world->getSpacePartition()->getDirectNeighbours(this);
	checkInteractions(lstSurroundingObjects);
	for (int i = 0; i < NB_INDIRECT_NEIGHBOURS_ZONES; i++) {
		lstSurroundingObjects = _world->getSpacePartition()->getIndirectNeighbours(this, i);
		checkInteractions(lstSurroundingObjects);
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
void AI::interact(GameObject * other)
{
}
