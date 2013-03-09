#ifndef _AI_H
#define _AI_H

#include "../World/Character.h"
#include "Behaviour.h"
#include "AIAction.h"
#include <stack>

#define DECISION_DELAY			0.5f

#define TRAITS_FRIENDLY			"friendly"

class AI : public Character
{
public:
	AI(JoS_Element& json);
    virtual ~AI();

    virtual void update(double delta);
    void setBehaviour(Behaviour * pBehaviour) { FREE(m_pBehaviour); m_pBehaviour = pBehaviour; };

private:
    AIAction * evaluateActionToDo();
    void checkInteractions();
    void checkInteractionsForList(list<PartitionableItem*>*);
    void interact(GameObject*);
    float computeObjectiveAttraction(Character * pOther);

    Behaviour * m_pBehaviour;
    double m_fInteractTimer;
    stack<AIAction*> m_pActionsStack;
};

#endif
