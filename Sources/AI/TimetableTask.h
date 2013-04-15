#ifndef _TIMETABLE_TASK_H
#define _TIMETABLE_TASK_H

#include "Task.h"

class TimetableTask : public Task
{
public:
	TimetableTask(int, double, AI*, JoS_Element*);
	~TimetableTask();

	double getTime() { return time; };
	int getIndex() { return index; };

private:
    int index;
    double time;
};

#endif
