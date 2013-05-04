#ifndef _AI_H
#define _AI_H

#include "../World/Character.h"
#include "Actions/AIAction.h"
#include "Timetable.h"
#include <stack>

#define DECISION_DELAY			0.5f
#define TRAITS_FRIENDLY			"friendly"

typedef tr1::function<bool (AI*, PartitionableItem*)> FilterPredicate;

class Discussion;
class SellingAction;

class AI : public Character
{
public:
	static AI * buildAI(string jsonFile);
    virtual ~AI();

    virtual string toString() const;
    virtual void update(double delta);
    virtual bool isAI() { return true; };
    bool isBusy();
    JoS_Element& pickDialog(JoS_Element&);
    void doAction(AIAction*);
    bool isSelling() { return pSellingAction != NULL; };
    SellingAction * getSellingAction() { return pSellingAction; };
    void setSellingAction(SellingAction * pSellingAction) { this->pSellingAction = pSellingAction; };
    void unsetSellingAction(SellingAction * pSellingAction) { if (this->pSellingAction == pSellingAction) { this->pSellingAction = NULL; }};

private:
	AI(JoS_Element * json);

	bool checkTimetable();
	AIAction * evaluateActionToDo();
    void getSurroundingObjects(list<PartitionableItem*>*, FilterPredicate filter);
    void checkInteractions();
    void interact(GameObject*);
    float computeObjectiveAttraction(Character * pOther);
    AIAction * startDiscussion(JoS_Element&, list<AI*>&);
    void joinDiscussion(Discussion*);
    void cleanFinishedActions();

    JoS_Element * json;
    double fInteractTimer;
    list<AIAction*> pActionsList;
    JoS_Union * dialogs;
    Timetable * pTimetable;
    Task * pCurrentTask;
    SellingAction * pSellingAction;
};

#endif
