#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "MovingObject.h"
#include "../Display/DisplayEngine.h"
#include "../Data/JoSon/JoSon.h"

#define TRAIT_MAX_VALUE		5

class Character : public MovingObject
{
public:
	Character(const JoS_Element &json);
    virtual ~Character();

    friend ostream& operator<< (ostream& stream, const Character& character);
    virtual void update(double delta);

    virtual bool isCharacter() { return true; };

    double getSpeed() { return speed; };
    void setSpeed(double speed) { this->speed = speed; };
    void setMoveTarget(Coords3D pos);
    long_hash * getTraits() { return &m_mapTraits; };

private:
    int getJsonInt(const JoS_Element &json, string name, int defaultVal, int capMin, int capMax);
    double getJsonDouble(const JoS_Element &json, string name, double defaultVal);
    string getJsonString(const JoS_Element &json, string name, string defaultVal);

    double speed;	// 3d unit / second
    long_hash m_mapTraits;
};

#endif
