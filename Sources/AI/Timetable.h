#ifndef _TIMETABLE_H
#define _TIMETABLE_H

#include "TimetableTask.h"

class Timetable
{
public:
	Timetable(JoS_Element*);
    ~Timetable();

    TimetableTask * findCurrentTask();

private:
    TimetableTask * findNextTask();

    JoS_Element * jsonTimeTablePtr;
    TimetableTask * currentTask;
    TimetableTask * nextTask;
};

#endif
