// -----------------------------------------------------------------
// IDLE ACTION
// -----------------------------------------------------------------
#include "IdleAction.h"
#include "DiscussionAction.h"
#include "../AI.h"

// -----------------------------------------------------------------
// Name : update
//	static
// -----------------------------------------------------------------
void IdleAction::idle(AI * ai)
{
	list<AI*> lstNeighbours;
	ai->getSurroundingAIs(&lstNeighbours);
	if (!lstNeighbours.empty()) {
		if (rand() % 10 == 0) {
			JoS_Element& dlg = ai->pickDialog();
			if (!dlg.isNull()) {
				startDiscussion(ai, dlg, lstNeighbours);
			}
		}
	}
}

// -----------------------------------------------------------------
// Name : startDiscussion
//	static
// -----------------------------------------------------------------
void IdleAction::startDiscussion(AI * ai, JoS_Element& dialog, list<AI*> &lstNeighbours)
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
