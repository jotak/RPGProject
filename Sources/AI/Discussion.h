#ifndef _DISCUSSION_H
#define _DISCUSSION_H

#include "../Data/JoSon/JoSon.h"
#include "AI.h"

#define DIALOG_CONDITION_IDLE		"idle"
#define DIALOG_CONDITION_BUSY		"busy"
#define DIALOG_CONDITION_HUNGRY		"hungry"

class Discussion
{
public:
	Discussion(const JoS_Element& discussion, AI * pFirstTalker);
    ~Discussion();

    void update(double delta);
    void join(AI * pParticipant);
    void leave(AI * pParticipant);

    AI * getLastTalker() { return m_pLastTalker; };

private:
    const JoS_Element& m_pLastSentence;
    AI * m_pLastTalker;
    list<AI*> m_pParticipants;
    double m_fSentenceTimer;
};

#endif
