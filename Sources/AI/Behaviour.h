#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

#include "../Utils/utils.h"

class Character;

class Behaviour
{
public:
	Behaviour(Character * ai) { m_pAI = ai; };
    virtual ~Behaviour() {};
    virtual void update(double delta) = 0;

protected:
    Character * m_pAI;
};

#endif
