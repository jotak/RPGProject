// -----------------------------------------------------------------
// IDLE ACTION
// -----------------------------------------------------------------
#include "IdleAction.h"
#include "DiscussionAction.h"
#include "BuyingAction.h"
#include "EatingAction.h"
#include "../AI.h"

bool isFood(InventoryObject * obj) {
	return obj->isFood();
}

// -----------------------------------------------------------------
// Name : update
//	static
// -----------------------------------------------------------------
void IdleAction::idle(AI * ai)
{
	// Is starving?
	if (ai->isStarving()) {
		list<InventoryObject*> inventory = ai->getInventory();
		list<InventoryObject*>::iterator it = find_if(inventory.begin(), inventory.end(), isFood);
		if (it != inventory.end()) {
			// Eat what you have!
			ai->doAction(new EatingAction(ai));
			return;
		}
	}

	vector<AI*> lstNeighbours;
	ai->getSurroundingAIs(&lstNeighbours);
	if (!lstNeighbours.empty()) {
		// Shuffle list, as there's no priority between neighbours
		random_shuffle(lstNeighbours.begin(), lstNeighbours.end());

		// Is starving?
		if (ai->isStarving()) {
			// Find someone who sells food
			for (AI * other : lstNeighbours) {
				if (other->isSelling(INVENTORY_TYPE_FOOD)) {
					int quantity = 1 + rand() % 4;
					ai->doAction(new BuyingAction(ai, other, INVENTORY_TYPE_FOOD, quantity));
					return;
				}
			}
		}

		// Want to talk?
		if (rand() % 10 == 0) {
			JoS_Element& dlg = ai->pickDialog();
			if (!dlg.isNull()) {
				startDiscussion(ai, dlg, lstNeighbours);
				return;
			}
		}

		// Want to buy something around?
	}
}

// -----------------------------------------------------------------
// Name : startDiscussion
//	static
// -----------------------------------------------------------------
void IdleAction::startDiscussion(AI * ai, JoS_Element& dialog, vector<AI*> &lstNeighbours)
{
	DiscussionAction * discussionAction = new DiscussionAction(ai);
	Discussion * pDiscussion = discussionAction->initiate(dialog);
	ai->doAction(discussionAction);
	for (AI * other : lstNeighbours) {
		joinDiscussion(other, pDiscussion);
	}
}

// -----------------------------------------------------------------
// Name : joinDiscussion
//	static
// -----------------------------------------------------------------
void IdleAction::joinDiscussion(AI * other, Discussion * pDiscussion)
{
	// TODO: evaluate if current action is actually more important than talking
	DiscussionAction * discussionAction = new DiscussionAction(other, pDiscussion);
	pDiscussion->join(discussionAction);
	other->doAction(discussionAction);
}
