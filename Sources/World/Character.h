#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "MovingObject.h"
#include "../Display/DisplayEngine.h"
#include "../Data/JoSon/JoSon.h"
#include "InventoryObject.h"

#define TRAIT_MAX_VALUE		5

//	"speed" stands for the speed characteristic; it must be relativised to board metrics
#define SPEED_CONVERT(s)	(2.0f + (double)s / 2.0f)

class Character : public MovingObject
{
public:
	Character(const JoS_Element& json);
    virtual ~Character();

    virtual string toString() const;
    virtual void update(double delta);

    virtual bool isCharacter() { return true; };

    // Getters / setters
    long_hash * getTraits() { return &mapTraits; };
    string getName() { return name; };
    double getSpeed() { return speed; };
    void setSpeed(double speed) { this->speed = speed; };
    double getLife() { return life; };
    void setLife(double life) { this->life = life; };
    double getHitPoints() { return hitPoints; };
    void setHitPoints(double hitPoints) { this->hitPoints = hitPoints; };
    bool canMove() { return bCanMove; };
    void setCanMove(bool bCanMove) { this->bCanMove = bCanMove; };

    // Gameplay methods
    void say(string);
    void goToGround(f3d);
    void goToGround(double, double);
    virtual bool isMoving() { return MovingObject::isMoving() || bHasMoveTarget; };
    bool hasMoveTarget() { return bHasMoveTarget; };
    void restoreLife(int);
    void addToInventory(InventoryObject*);

    // Static stuff
    static void initData();
    static void releaseData();
    static JoS_Element& getCommonDialogs(string name);
    static float getTraitsRelation(string from, string towards);

protected:
    static JoSon * TraitsRelations;
    static jos_map CommonDialogs;

private:
    void doMove(double);

    string name;
    int speed;	// arbitrary scale; convert it to display/physic engine using macro "SPEED_CONVERT"
    int hitPoints;
    int life;
    long_hash mapTraits;
    bool bCanMove;
    bool bHasMoveTarget;
    f3d moveTarget;
    list<InventoryObject*> inventory;
};

#endif
