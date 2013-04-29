#ifndef _EATING_ACTION_H
#define _EATING_ACTION_H

#include "AIAction.h"
#include "../../World/FoodObject.h"

class EatingAction : public AIAction
{
public:
	EatingAction(AI*);
    virtual ~EatingAction();

    virtual void update(double);

private:
    void eat(int);

    double m_fTimer;
};

#endif
