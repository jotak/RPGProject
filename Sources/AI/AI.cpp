// -----------------------------------------------------------------
// AI
// -----------------------------------------------------------------
#include "AI.h"
#include "../Managers/WorldManager.h"
#include "../Managers/DebugManager.h"
#include "../Physics/SpacePart.h"
#include "DiscussionAction.h"

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
	FREESTACK(m_pActionsStack);
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void AI::update(double delta)
{
	m_fInteractTimer -= delta;
	if (m_fInteractTimer <= 0) {
		// Time to take a decision!
		m_fInteractTimer = DECISION_DELAY;
		AIAction * newAction = evaluateActionToDo();
		if (newAction != NULL) {
			// There's something we want to do
			m_pActionsStack.push(newAction);
		}
	}

	if (!m_pActionsStack.empty()) {
		// Do what we want to do
		AIAction * currentAction = m_pActionsStack.top();
		currentAction->update(delta);
		if (currentAction->isFinished()) {
			// This task is done
			delete currentAction;
			m_pActionsStack.pop();
		}
	}

//	if (m_pBehaviour != NULL) {
//		m_pBehaviour->update(delta);
//	}
	Character::update(delta);
}

bool isSurrounding(AI * that, PartitionableItem * pItem) {
	if (pItem != that) {
		// Skip "this" since the AI itself is in the list
		f3d vec = that->getPosition() - pItem->getPosition();
		if (vec.getsize() < AI_INTERACTION_RADIUS) {
			return true;
		}
	}
	return false;
}
bool isSurroundingCharacter(AI * that, PartitionableItem * pItem) {
	return ((GameObject*)pItem)->isCharacter() && isSurrounding(that, pItem);
}
bool isSurroundingAI(AI * that, PartitionableItem * pItem) {
	return ((GameObject*)pItem)->isAI() && isSurrounding(that, pItem);
}

// -----------------------------------------------------------------
// Name : evaluateActionToDo
// -----------------------------------------------------------------
AIAction * AI::evaluateActionToDo()
{
	AIAction * currentAction = NULL;
	if (!m_pActionsStack.empty()) {
		currentAction = m_pActionsStack.top();
	}

	// Nothing to do? 1/10 chances to start banality discussion with people arround
	if (currentAction == NULL) {
		list<PartitionableItem*> lstSurrounding;
		list<AI*> lstNeighbours;

		getSurroundingObjects(&lstSurrounding, isSurroundingAI);
		transform(lstSurrounding.begin(), lstSurrounding.end(), back_inserter(lstNeighbours), static_caster<PartitionableItem*, AI*>());
		if (!lstNeighbours.empty()) {
			if (rand() % 10 == 0) {
				const JoS_Element& dlg = pickDialog(*Character::Dialogs);
				if (!dlg.isNull()) {
					return startDiscussion(dlg, lstNeighbours);
				}
			}
		}
	}
	return NULL;
}

// -----------------------------------------------------------------
// Name : pickDialog
// -----------------------------------------------------------------
const JoS_Element& AI::pickDialog(const JoS_Element& listItems)
{
	list<int> lstAcceptableIdx;
	for (int itemIdx = 0; itemIdx < listItems.size(); itemIdx++) {
		const JoS_Element& item = listItems[itemIdx];
		const JoS_Element& lstCondStates = item["condState"];
		bool bMatchConditions = true;
		for (int j = 0; j < lstCondStates.size(); j++) {
			string condition = lstCondStates[j].toString();
			if (condition == DIALOG_CONDITION_IDLE) {
				bMatchConditions &= !isBusy();
				continue;
			}
			if (condition == DIALOG_CONDITION_BUSY) {
				bMatchConditions &= isBusy();
				continue;
			}
			if (condition == DIALOG_CONDITION_HUNGRY) {
				bMatchConditions &= isHungry();
				continue;
			}
		}
		if (bMatchConditions) {
			// This item is acceptable
			lstAcceptableIdx.push_back(itemIdx);
		}
	}
	if (!lstAcceptableIdx.empty()) {
		int rnd = rand() % lstAcceptableIdx.size();
		list<int>::iterator it = lstAcceptableIdx.begin();
		for (; rnd > 0; it++, rnd--);
		return listItems[*it];
	}
	return JoS_Null::JoSNull;
}

// -----------------------------------------------------------------
// Name : startDiscussion
// -----------------------------------------------------------------
AIAction * AI::startDiscussion(const JoS_Element& dialog, list<AI*> &lstNeighbours)
{
	Discussion * pDiscussion = new Discussion(dialog, this);
	for (AI * ai : lstNeighbours) {
		pDiscussion->join(ai);
	}
	return new DiscussionAction(this, pDiscussion);
}

// -----------------------------------------------------------------
// Name : suggestAction
//	Returns true if action is accepted
// -----------------------------------------------------------------
bool AI::suggestAction(AIAction * pAction)
{
	m_pActionsStack.push(pAction);
	return true;
}

// -----------------------------------------------------------------
// Name : checkInteractions
// -----------------------------------------------------------------
void AI::checkInteractions()
{
	list<PartitionableItem*> lstSurrounding;
	getSurroundingObjects(&lstSurrounding, isSurrounding);

	for (PartitionableItem * pItem : lstSurrounding) {
		interact((GameObject*) pItem);
	}
}

// --------------------------------------------------------------------
// Name : getSurroundingObjects
//	Initialize lstSurroundingObjects as empty list when calling method
// --------------------------------------------------------------------
void AI::getSurroundingObjects(list<PartitionableItem*> * lstReturn, FilterPredicate filter)
{
	list<PartitionableItem*> lstSurroundingObjects;
	list<PartitionableItem*> * lst = _world->getSpacePartition()->getDirectNeighbours(this);
	lstSurroundingObjects.insert(lstSurroundingObjects.end(), lst->begin(), lst->end());
	for (int i = 0; i < NB_INDIRECT_NEIGHBOURS_ZONES; i++) {
		lst = _world->getSpacePartition()->getIndirectNeighbours(this, i);
		if (lst != NULL) {
			lstSurroundingObjects.insert(lstSurroundingObjects.end(), lst->begin(), lst->end());
		}
	}

	// Apply filters
	for (PartitionableItem * pItem : lstSurroundingObjects) {
		if (filter(this, pItem)) {
			lstReturn->push_back(pItem);
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
	float attraction = 0.0f;
	long_hash * pThisTraits = getTraits();
	long_hash * pOtherTraits = pOther->getTraits();
	for (pair<string, long> from : *pThisTraits) {
		for (pair<string, long> to : *pOtherTraits) {
			// fRelation [-1,1]
			float fRelation = (float)from.second/*[0,5]*/ * (float)to.second/*[0,5]*/ * getTraitsRelation(from.first, to.first)/*[0,1]*/ / (float)(TRAIT_MAX_VALUE * TRAIT_MAX_VALUE);
			// Square it so that an "extreme" relation counts for more than a neutral one
			attraction += (fRelation * abs(fRelation));
		}
	}

	// "Friendly" traits automatically improves attraction
	float friendly = ((float)(*pThisTraits)[TRAITS_FRIENDLY]) / (float)(TRAIT_MAX_VALUE);
	attraction += friendly / 2;

	friendly = ((float)(*pOtherTraits)[TRAITS_FRIENDLY]) / (float)(TRAIT_MAX_VALUE);
	attraction += friendly;

	// charismatic, charmer, cold

	return attraction;
}

// -----------------------------------------------------------------
// Name : isBusy
// -----------------------------------------------------------------
bool AI::isBusy()
{
	return !m_pActionsStack.empty();
}

// -----------------------------------------------------------------
// Name : isHungry
// -----------------------------------------------------------------
bool AI::isHungry()
{
	return true;
}
