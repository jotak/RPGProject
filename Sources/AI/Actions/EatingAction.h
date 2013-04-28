#ifndef _EATING_ACTION_H
#define _EATING_ACTION_H

#include "AIAction.h"

class EatingAction : public AIAction
{
public:
	EatingAction(AI*);
    virtual ~EatingAction();

    virtual void update(double);
    virtual bool isFinished() { return AIAction::isFinished(); };

private:
    double m_fTimer;
};

#endif
