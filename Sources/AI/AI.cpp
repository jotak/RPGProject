// -----------------------------------------------------------------
// AI
// -----------------------------------------------------------------
#include "AI.h"
#include "../Managers/WorldManager.h"
#include "../Managers/DebugManager.h"
#include "../Physics/SpacePart.h"
#include "Actions/DiscussionAction.h"

// -----------------------------------------------------------------
// Name : AI
// -----------------------------------------------------------------
AI::AI(JoS_Element * json) : Character(*json)
{
	this->json = json;
	fInteractTimer = 0;
	pCurrentTask = NULL;

	// Dialogs
	dialogs = new JoS_Union((*json)["dialogs"]);
	JoS_Element& addDialogs = (*json)["inheritDialogs"];
	if (addDialogs.isLeaf()) {
		dialogs->concat(Character::getCommonDialogs(addDialogs.toString()));
	}

	// Timetable
	JoS_Element& jsonTimetable = (*json)["timetable"];
	if (jsonTimetable.isList()) {
		pTimetable = new Timetable(this, &jsonTimetable);
		// Initialize table by finding current task
		checkTimetable();
		if (pCurrentTask == NULL) {
			// No task => invalid time table => no time table
			_debug->error(getName() + " has invalid timetable");
			FREE(pTimetable);
		}
	} else {
		pTimetable = NULL;
	}
}

// -----------------------------------------------------------------
// Name : ~AI
// -----------------------------------------------------------------
AI::~AI()
{
	FREESTACK(pActionsStack);
	FREE(json);
	FREE(dialogs);
	FREE(pTimetable);
}

// -----------------------------------------------------------------
// Name : toString
// -----------------------------------------------------------------
string AI::toString() const {
	std::ostringstream oss;
	oss << Character::toString();
	return oss.str();
}

// -----------------------------------------------------------------
// Name : buildAI
// -----------------------------------------------------------------
AI * AI::buildAI(string jsonFile)
{
	string sError;
	JoSon * json = JoSon::fromFile(string(AI_PATH) + jsonFile, &sError);
	if (json == NULL) {
		_debug->error(string("Error when loading json: ") + jsonFile + " - Error message: " + sError);
		return NULL;
	} else {
		return new AI(json);
	}
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void AI::update(double delta)
{
	fInteractTimer -= delta;
	if (fInteractTimer <= 0) {
		// Time to take a decision!
		fInteractTimer = DECISION_DELAY;
		bool didSomething = false;
		if (pTimetable != NULL) {
			didSomething = checkTimetable();
		}
		if (!didSomething && pCurrentTask != NULL) {
			didSomething = pCurrentTask->checkThen();
		}
		if (!didSomething) {
			AIAction * newAction = evaluateActionToDo();
			if (newAction != NULL) {
				// There's something we want to do
				pActionsStack.push(newAction);
			}
		}
	}

	cleanFinishedActions();
	if (!pActionsStack.empty()) {
		// Do what we want to do
		AIAction * currentAction = pActionsStack.top();
		currentAction->update(delta);
	}

	Character::update(delta);
}

bool isSurrounding(AI * that, PartitionableItem * pItem) {
	if (pItem != that) {
		// Skip "this" since the AI itself is in the list
		f3d vec = that->getPosition() - pItem->getPosition();
		if (vec.getSize() < AI_INTERACTION_RADIUS) {
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
// Name : cleanFinishedActions
// -----------------------------------------------------------------
void AI::cleanFinishedActions()
{
	while (!pActionsStack.empty()) {
		AIAction * action = pActionsStack.top();
		if (action->isFinished()) {
			delete action;
			pActionsStack.pop();
		} else {
			break;
		}
	}
}

// -----------------------------------------------------------------
// Name : checkTimetable
//	Check AI's time table to see if we need to start a new task
// -----------------------------------------------------------------
bool AI::checkTimetable()
{
	Task * pPreviousTask = pCurrentTask;
	pCurrentTask = pTimetable->updateCurrentTask();
	return (pPreviousTask != pCurrentTask);
}

// -----------------------------------------------------------------
// Name : doAction
// -----------------------------------------------------------------
void AI::doAction(AIAction * pAction)
{
	pActionsStack.push(pAction);
}

// -----------------------------------------------------------------
// Name : evaluateActionToDo
// -----------------------------------------------------------------
AIAction * AI::evaluateActionToDo()
{
	AIAction * currentAction = NULL;
	if (!pActionsStack.empty()) {
		currentAction = pActionsStack.top();
	}

	// Nothing to do? 1/10 chances to start banality discussion with people arround
	if (currentAction == NULL) {
		list<PartitionableItem*> lstSurrounding;
		list<AI*> lstNeighbours;

		getSurroundingObjects(&lstSurrounding, isSurroundingAI);
		transform(lstSurrounding.begin(), lstSurrounding.end(), back_inserter(lstNeighbours), static_caster<PartitionableItem*, AI*>());
		if (!lstNeighbours.empty()) {
			if (rand() % 10 == 0) {
				JoS_Element& dlg = pickDialog(*dialogs);
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
JoS_Element& AI::pickDialog(JoS_Element& listItems)
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
			if (condition == DIALOG_CONDITION_TIRED) {
				bMatchConditions &= isTired();
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
AIAction * AI::startDiscussion(JoS_Element& dialog, list<AI*> &lstNeighbours)
{
	DiscussionAction * discussionAction = new DiscussionAction(this);
	Discussion * pDiscussion = discussionAction->initiate(dialog);
	for (AI * ai : lstNeighbours) {
		ai->joinDiscussion(pDiscussion);
	}
	return discussionAction;
}

// -----------------------------------------------------------------
// Name : joinDiscussion
// -----------------------------------------------------------------
void AI::joinDiscussion(Discussion * pDiscussion)
{
	// TODO: evaluate if current action is actually more important than talking
	DiscussionAction * discussionAction = new DiscussionAction(this, pDiscussion);
	pDiscussion->join(discussionAction);
	pActionsStack.push(discussionAction);
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
	return !pActionsStack.empty();
}
