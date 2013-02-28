#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "MovingObject.h"
#include "../Display/DisplayEngine.h"
#include "../AI/Behaviour.h"

class Character : public MovingObject
{
public:
	Character(double speed);
    virtual ~Character();

    virtual void update(double delta);

    double getSpeed() { return speed; };
    void setSpeed(double speed) { this->speed = speed; };
    void setMoveTarget(Coords3D pos);
    void setBehaviour(Behaviour * pBehaviour) { FREE(m_pBehaviour); m_pBehaviour = pBehaviour; };

private:
    double speed;	// 3d unit / second
    Behaviour * m_pBehaviour;
};

#endif
