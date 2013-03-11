#ifndef _DISCUSSION_ACTION_H
#define _DISCUSSION_ACTION_H

#include "AIAction.h"
#include "Discussion.h"

class DiscussionAction : public AIAction
{
public:
	DiscussionAction(AI * ai, Discussion * pDiscussion);
    virtual ~DiscussionAction();

    virtual void update(double delta);
    virtual bool isFinished();

private:
    Discussion * m_pDiscussion;
};

#endif
