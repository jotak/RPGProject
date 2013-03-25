#ifndef _AI_H
#define _AI_H

#include "../World/Character.h"
#include "Behaviour.h"
#include "AIAction.h"
#include <stack>

#define DECISION_DELAY			0.5f
#define TRAITS_FRIENDLY			"friendly"

typedef tr1::function<bool (AI*, PartitionableItem*)> FilterPredicate;

class Discussion;

class AI : public Character
{
public:
	static AI * buildAI(string jsonFile);
    virtual ~AI();

    virtual void update(double delta);
    void setBehaviour(Behaviour * pBehaviour) { FREE(this->pBehaviour); this->pBehaviour = pBehaviour; };
    virtual bool isAI() { return true; };
    bool isBusy();
    bool isHungry();
    JoS_Element& pickDialog(JoS_Element&);

private:
	AI(JoS_Element * json);

	AIAction * evaluateActionToDo();
    void getSurroundingObjects(list<PartitionableItem*>*, FilterPredicate filter);
    void checkInteractions();
    void interact(GameObject*);
    float computeObjectiveAttraction(Character * pOther);
    AIAction * startDiscussion(JoS_Element&, list<AI*>&);
    void joinDiscussion(Discussion*);

    JoS_Element * json;
    Behaviour * pBehaviour;
    double fInteractTimer;
    stack<AIAction*> pActionsStack;
    JoS_Union * dialogs;
};

#endif
