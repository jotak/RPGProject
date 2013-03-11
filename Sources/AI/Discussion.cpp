// -----------------------------------------------------------------
// DISCUSSION
// -----------------------------------------------------------------
#include "Discussion.h"
#include "DiscussionAction.h"

// -----------------------------------------------------------------
// Name : Discussion
// -----------------------------------------------------------------
Discussion::Discussion(const JoS_Element& discussion, AI * pFirstTalker)
	: m_pLastSentence(discussion)
{
	m_pLastTalker = pFirstTalker;
	string sentence = discussion["text"].toString();
	m_pLastTalker->say(sentence);
	m_fSentenceTimer = sentence.length() / 30.0f;	// 10 characters per second
}

// -----------------------------------------------------------------
// Name : ~Discussion
// -----------------------------------------------------------------
Discussion::~Discussion()
{
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void Discussion::update(double delta)
{
	if (m_fSentenceTimer > 0) {
		m_fSentenceTimer -= delta;
	}
}

// -----------------------------------------------------------------
// Name : join
// -----------------------------------------------------------------
void Discussion::join(AI * pParticipant)
{
	DiscussionAction * pListening = new DiscussionAction(pParticipant, this);
	if (pParticipant->suggestAction(pListening)) {
		m_pParticipants.push_back(pParticipant);
	} else {
		delete pListening;
	}
}

// -----------------------------------------------------------------
// Name : leave
// -----------------------------------------------------------------
void Discussion::leave(AI * pParticipant)
{
}
