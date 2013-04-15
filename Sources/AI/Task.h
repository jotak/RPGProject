#ifndef _TASK_H
#define _TASK_H

#include "../Data/JoSon/JoSon.h"
#include "../Utils/utils.h"

class AI;
class AIAction;

class Task
{
public:
	Task(AI*, JoS_Element*);
	virtual ~Task();

	void start();
	bool checkThen();

private:
	void executeGoTo(JoS_Element&);
	void executeStartActivity(JoS_Element&);

    JoS_Element * taskDataPtr;
    AI * m_pAI;
    bool isGoingTo;
    f3d goingTo;
    list<AIAction*> doingActions;
    Task * currentSubtask;
};

#endif
