#ifndef _GOTO_BEHAVIOUR_H
#define _GOTO_BEHAVIOUR_H

#include "Behaviour.h"

class GoToBehaviour : public Behaviour
{
public:
	GoToBehaviour(f3d target, Character * ai);
    virtual ~GoToBehaviour();

    virtual void update(double delta);

private:
    f3d m_Target;
};

#endif
