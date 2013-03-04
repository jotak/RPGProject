#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "MovingObject.h"
#include "../Display/DisplayEngine.h"

class JoS_Element;

class Character : public MovingObject
{
public:
	Character(JoS_Element * json);
    virtual ~Character();

    friend ostream& operator<< (ostream& stream, const Character& character);
    virtual void update(double delta);

    double getSpeed() { return speed; };
    void setSpeed(double speed) { this->speed = speed; };
    void setMoveTarget(Coords3D pos);

private:
    int getJsonInt(JoS_Element * json, string name, int defaultVal);
    double getJsonDouble(JoS_Element * json, string name, double defaultVal);
    string getJsonString(JoS_Element * json, string name, string defaultVal);

    double speed;	// 3d unit / second
    long_hash m_mapTraits;
};

#endif
