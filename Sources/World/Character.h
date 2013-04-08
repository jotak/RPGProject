#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "MovingObject.h"
#include "../Display/DisplayEngine.h"
#include "../Data/JoSon/JoSon.h"

#define TRAIT_MAX_VALUE		5

class Character : public MovingObject
{
public:
	Character(const JoS_Element& json);
    virtual ~Character();

    virtual string toString() const;
    virtual void update(double delta);

    virtual bool isCharacter() { return true; };

    string getName() { return name; };
    double getSpeed() { return speed; };
    void setSpeed(double speed) { this->speed = speed; };
    void setMoveTarget(Coords3D pos);
    long_hash * getTraits() { return &mapTraits; };
    double get3DSpeed();
    void say(string);

    static void initData();
    static void releaseData();
    static JoS_Element& getCommonDialogs(string name);
    static float getTraitsRelation(string from, string towards);

protected:
    static JoSon * TraitsRelations;
    static jos_map CommonDialogs;

private:
    string name;
    double speed;	// 3d unit / second
    long_hash mapTraits;
};

#endif
