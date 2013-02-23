#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "MovingObject.h"
#include "../Display/DisplayEngine.h"

class Character : public MovingObject
{
public:
	Character(double speed);
    virtual ~Character();

    void update(double delta);

    double getSpeed() { return speed; };
    void setSpeed(double speed) { this->speed = speed; };
    void setMoveTarget(Coords3D pos) { moveTarget = pos; };
    void unsetMoveTarget() { moveTarget.z = FARPLANE; };
    bool hasMoveTarget() { return moveTarget.z == FARPLANE; };

private:
    double speed;	// 3d unit / second
    Coords3D moveTarget;
};

#endif
