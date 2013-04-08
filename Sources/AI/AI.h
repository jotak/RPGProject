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

class AI : public Character
{
public:
	static AI * buildAI(string jsonFile);
    virtual ~AI();

    virtual string toString() const;
    virtual void update(double delta);
    virtual bool isAI() { return true; };
    bool isBusy();
    bool isHungry();
    JoS_Element& pickDialog(JoS_Element&);

private:
	AI(JoS_Element * json);

	void checkTimetable();
	AIAction * evaluateActionToDo();
    void getSurroundingObjects(list<PartitionableItem*>*, FilterPredicate filter);
    void checkInteractions();
    void interact(GameObject*);
    float computeObjectiveAttraction(Character * pOther);
    AIAction * startDiscussion(JoS_Element&, list<AI*>&);
    void joinDiscussion(Discussion*);

    JoS_Element * json;
    double fInteractTimer;
    stack<AIAction*> pActionsStack;
    JoS_Union * dialogs;
    Timetable * pTimetable;
    TimetableTask * pCurrentTask;
};

#endif
