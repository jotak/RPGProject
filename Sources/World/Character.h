#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "MovingObject.h"
#include "../Display/DisplayEngine.h"

class Character : public MovingObject
{
public:
	Character(double speed);
    virtual ~Character();

    virtual void update(double delta);

    double getSpeed() { return speed; };
    void setSpeed(double speed) { this->speed = speed; };
    void setMoveTarget(Coords3D pos);

private:
    double speed;	// 3d unit / second
};

#endif
