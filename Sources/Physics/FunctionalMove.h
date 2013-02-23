#ifndef _FUNCTIONAL_MOVE_H
#define _FUNCTIONAL_MOVE_H

#include "Movement.h"
#include "../Utils/utils.h"

typedef tr1::function<double (double)> MoveFunction;

class FunctionalMove : public Movement
{
public:
	FunctionalMove(Coords3D vector, double fFullSpeed, MoveFunction func);
    virtual ~FunctionalMove();

    virtual Coords3D apply(double delta, Coords3D position);

private:
    Coords3D m_Vector;
    double m_fFullSpeed;
    MoveFunction m_Func;
    double m_f1DPos;
};

#endif
