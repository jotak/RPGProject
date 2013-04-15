// -----------------------------------------------------------------
// TASK
//	A task is a set of things to do defined in json file.
//	One task can trigger several actions...
// -----------------------------------------------------------------
#include "Task.h"
#include "AI.h"
#include "../Managers/DebugManager.h"
#include "../Data/JSonUtil.h"
#include "Actions/GoToAction.h"

#define INSTRUCTION_GOTO				"goTo"
#define INSTRUCTION_START_ACTIVITY		"startActivity"
#define INSTRUCTION_THEN				"then"

// -----------------------------------------------------------------
// Name : Task
// -----------------------------------------------------------------
Task::Task(AI * pAI, JoS_Element * taskData)
{
	this->taskDataPtr = taskData;
	m_pAI = pAI;
	isGoingTo = false;
	currentSubtask = NULL;
}

// -----------------------------------------------------------------
// Name : ~Task
// -----------------------------------------------------------------
Task::~Task()
{
	FREE(currentSubtask);
}

// -----------------------------------------------------------------
// Name : start
// -----------------------------------------------------------------
void Task::start()
{
	JoS_Element& taskData = *taskDataPtr;
	if (!taskData[INSTRUCTION_GOTO].isNull()) {
		executeGoTo(taskData[INSTRUCTION_GOTO]);
	}
	if (!taskData[INSTRUCTION_START_ACTIVITY].isNull()) {
		executeStartActivity(taskData[INSTRUCTION_START_ACTIVITY]);
	}
}

// -----------------------------------------------------------------
// Name : checkThen
//	Task may looks like:
//task: {
//	goTo: [6, 3.5],
//	then: {
//		startActivity: {
//			name: fishing,
//			ability: 3
//		}
//	}
//}
//
//	the "then" keyword refers to a subtask that will be executed once the current task is finished
// The succession of "task", "then #1", "then #2" etc. are chained (each node contains its child, "task" is the root node).
// -----------------------------------------------------------------
bool Task::checkThen()
{
	// If currentSubtask is not NULL, then we are currently executing a subtask
	if (currentSubtask != NULL) {
		return currentSubtask->checkThen();
	} else {
		// Not in a subtask => check if that task is finished
		// If true, start the subtask
		JoS_Element& taskData = *taskDataPtr;
		if (!taskData[INSTRUCTION_THEN].isNull()) {
			if (isGoingTo && m_pAI->isCloseTo(goingTo)) {
				isGoingTo = false;
			}
			for (list<AIAction*>::iterator it = doingActions.begin(); it != doingActions.end(); ++it) {
				AIAction * action = *it;
				if (action->isFinished()) {
					it = doingActions.erase(it);
				}
			}
			if (doingActions.empty() && !isGoingTo) {
				currentSubtask = new Task(m_pAI, &(taskData[INSTRUCTION_THEN]));
				currentSubtask->start();
				return true;
			}
		}
		return NULL;
	}
}

// -----------------------------------------------------------------
// Name : executeGoTo
// -----------------------------------------------------------------
void Task::executeGoTo(JoS_Element& json)
{
	if (json.isList()) {
		double x = JSonUtil::getDouble(json[0]);
		double y = JSonUtil::getDouble(json[1]);
		cout << m_pAI->getName() << " goes to (" << x << ", " << y << ")" << endl;
		m_pAI->goToGround(x, y);
	} else {
		_debug->error("Invalid json, goTo expects list.");
	}
}

// -----------------------------------------------------------------
// Name : executeStartActivity
// -----------------------------------------------------------------
void Task::executeStartActivity(JoS_Element& json)
{
	if (json.isMap()) {
		cout << m_pAI->getName() << " starts activity " << json["name"].toString() << endl;
	} else {
		_debug->error("Invalid json, startActivity expects map.");
	}
}