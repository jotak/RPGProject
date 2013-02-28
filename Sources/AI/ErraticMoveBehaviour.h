#ifndef _ERRATIC_MOVE_BEHAVIOUR_H
#define _ERRATIC_MOVE_BEHAVIOUR_H

#include "Behaviour.h"

class ErraticMoveBehaviour : public Behaviour
{
public:
	ErraticMoveBehaviour(Character * ai);
    virtual ~ErraticMoveBehaviour();

    virtual void update(double delta);

private:
    double m_fWait;
};

#endif
