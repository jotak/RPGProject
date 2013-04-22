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
	void stop();
	bool checkThen();

private:
	void executeGoTo(const JoS_Element&);
	void executeStartActivity(const JoS_Element&);

    JoS_Element * taskDataPtr;
    AI * m_pAI;
    bool isGoingTo;
    f3d goingTo;
    list<AIAction*> doingActions;
    Task * currentSubtask;
};

#endif
