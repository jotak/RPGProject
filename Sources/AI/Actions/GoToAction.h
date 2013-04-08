#ifndef _GOTO_ACTION_H
#define _GOTO_ACTION_H

#include "AIAction.h"

class GoToAction : public AIAction
{
public:
	GoToAction(f3d target, AI * ai);
    virtual ~GoToAction();

    virtual void update(double delta);

private:
    f3d m_Target;
};

#endif
