#ifndef _TIMETABLE_TASK_H
#define _TIMETABLE_TASK_H

#include "../Data/JoSon/JoSon.h"

class TimetableTask
{
public:
	TimetableTask(int index, double time, JoS_Element * taskData) {
		this->index = index;
		this->time = time;
		this->taskData = taskData;
	}

	double getTime() { return time; };
	int getIndex() { return index; };

private:
    int index;
    double time;
    JoS_Element * taskData;
};

#endif
