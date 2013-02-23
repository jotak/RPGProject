#ifndef _MOVEMENT_H
#define _MOVEMENT_H

enum MoveState {
	Inactive = 0,
	InProgress,
	Finished
};

class Movement
{
public:
    Movement() { m_State = Inactive; };
    virtual ~Movement() {};

    virtual Coords3D apply(double delta, Coords3D position) = 0;

protected:
    MoveState m_State;
};

#endif
