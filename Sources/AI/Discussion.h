#ifndef _DISCUSSION_H
#define _DISCUSSION_H

#include "../Data/JoSon/JoSon.h"
#include "AI.h"
#include "../Utils/GarbageCollector.h"

#define DIALOG_CONDITION_IDLE		"idle"
#define DIALOG_CONDITION_BUSY		"busy"
#define DIALOG_CONDITION_HUNGRY		"hungry"
#define DIALOG_CONDITION_TIRED		"tired"

class DiscussionAction;

class Discussion : public Garbageable
{
public:
	Discussion(JoS_Element&, DiscussionAction*);
    ~Discussion();

    void join(DiscussionAction * pParticipant);
    void notifyStoppedTalking(DiscussionAction*);

private:
    JoS_Element * m_pCurrentSentence;
    list<DiscussionAction*> m_pParticipants;
};

#endif
