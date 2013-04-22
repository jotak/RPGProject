#ifndef _FOOD_OBJECT_H
#define _FOOD_OBJECT_H

#include "InventoryObject.h"
#include "Character.h"

class FoodObject : public InventoryObject
{
public:
	FoodObject(int restore, int price, int weight, string name) : InventoryObject(price, weight, name)
		{ setRestore(restore); };
    virtual ~FoodObject() {};

    virtual void eat(Character * pCharacter) { pCharacter->restoreLife(restore); };

    int getRestore() { return restore; };
    void setRestore(int restore) { this->restore = restore; };

private:
    int restore;
};

#endif
