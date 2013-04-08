// -----------------------------------------------------------------
// TIME TABLE
// -----------------------------------------------------------------
#include "Timetable.h"
#include "../World/WorldTime.h"
#include "../Data/JSonUtil.h"

#define JSON_TASK_KEY		"task"

// -----------------------------------------------------------------
// Name : Timetable
// -----------------------------------------------------------------
Timetable::Timetable(JoS_Element * jsonTimeTablePtr)
{
    this->jsonTimeTablePtr = jsonTimeTablePtr;
    currentTask = NULL;
    nextTask = NULL;
}

// -----------------------------------------------------------------
// Name : ~Timetable
// -----------------------------------------------------------------
Timetable::~Timetable()
{
	FREE(currentTask);
	FREE(nextTask);
}

// -----------------------------------------------------------------
// Name : findCurrentTask
// -----------------------------------------------------------------
TimetableTask * Timetable::findCurrentTask()
{
	// Get "now" in hours
	double nowHour = TIME_IN_HOURS(_time->getTime());

	if (currentTask == NULL) {
		// First initialization
		JoS_Element& jsonTimeTable = *jsonTimeTablePtr;
		if (jsonTimeTable.isList()) {
			int len = jsonTimeTable.size();
			double closestStartAt = -1;
			int closestTask = -1;
			// For each task
			for (int iTask = 0; iTask < len; iTask++) {
				JoS_Element& task = jsonTimeTable[iTask];
				double startAt = JSonUtil::getDouble(task, -1);
				// Find either highest task hour that is lower than now, else absolute highest task hour (that is, latest before midnight)
				// This algorithm assumes that tasks are ordered from earliest to latest.
				if (startAt <= nowHour || closestTask == -1 || closestStartAt > nowHour) {
					closestStartAt = startAt;
					closestTask = iTask;
				}
			}
			if (closestTask >= 0) {
				currentTask = new TimetableTask(closestTask, closestStartAt, &(jsonTimeTable[closestTask][JSON_TASK_KEY]));
				nextTask = findNextTask();
			}
		}
	} else {
		// We've already a "currentTask". Check that nextTask has not begun. nextTask must not be NULL.
		if (nowHour >= nextTask->getTime()) {
			delete currentTask;
			currentTask = nextTask;
			nextTask = findNextTask();
		}
	}
	return currentTask;
}

// -----------------------------------------------------------------
// Name : findNextTask
// -----------------------------------------------------------------
TimetableTask * Timetable::findNextTask()
{
	JoS_Element& jsonTimeTable = *jsonTimeTablePtr;
	int iNextTask = (currentTask->getIndex() + 1) % jsonTimeTable.size();
	JoS_Element& jsonTask = jsonTimeTable[iNextTask];
	double startAt = JSonUtil::getDouble(jsonTask);
	return new TimetableTask(iNextTask, startAt, &(jsonTask[JSON_TASK_KEY]));
}
