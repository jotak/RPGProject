#ifndef _TIMETABLE_H
#define _TIMETABLE_H

#include "TimetableTask.h"

class Timetable
{
public:
	Timetable(AI*, JoS_Element*);
    ~Timetable();

    TimetableTask * updateCurrentTask();

private:
    TimetableTask * findNextTask();

    JoS_Element * jsonTimeTablePtr;
    TimetableTask * currentTask;
    TimetableTask * nextTask;
    AI * m_pAI;
};

#endif
