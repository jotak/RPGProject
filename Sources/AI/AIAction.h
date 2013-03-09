#ifndef _AI_ACTION_H
#define _AI_ACTION_H

#include "../Utils/utils.h"

class AIAction
{
public:
	AIAction(Character * ai) { m_pAI = ai; };
    virtual ~AIAction() {};
    virtual void update(double delta) = 0;
    virtual bool isFinished() = 0;

protected:
    Character * m_pAI;
};

#endif
