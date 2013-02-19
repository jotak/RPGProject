#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "GameObject.h"
#include "Collidable.h"

class MovingObject : public GameObject
{
public:
	MovingObject() {};
    virtual ~MovingObject() {};

    int getRadius() { return radius; };
    void setRadius(int radius) { this->radius = radius; };

    virtual void collide(Collidable * pCollidable) {};

private:
    int radius;
};

#endif
