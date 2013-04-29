// -----------------------------------------------------------------
// EATING ACTION
// -----------------------------------------------------------------
#include "EatingAction.h"
#include "../AI.h"

#define EATING_DURATION			600 // 10 min

// -----------------------------------------------------------------
// Name : EatingAction
// -----------------------------------------------------------------
EatingAction::EatingAction(AI * ai) : AIAction(ai)
{
	m_fTimer = 0;
}

// -----------------------------------------------------------------
// Name : ~EatingAction
// -----------------------------------------------------------------
EatingAction::~EatingAction()
{
}

// -----------------------------------------------------------------
// Name : eat
// -----------------------------------------------------------------
void EatingAction::eat(int energyNeeded)
{
	// Find food in player's inventory
	// Best food is a food that doesn't restore more than what is needed
	// okFood can restore more
	FoodObject * okFood = NULL;
	list<InventoryObject*> inventory = m_pAI->getInventory();
	for (list<InventoryObject*>::iterator it = inventory.begin(); it != inventory.end(); ++it) {
		if ((*it)->isFood()) {
			FoodObject * food = (FoodObject*) *it;
			if (food->getRestore() <= energyNeeded) {
				m_pAI->restoreEnergy(food->getRestore());
				m_pAI->resetHungryState();
				inventory.erase(it);
				return;
			}
			if (okFood == NULL) {
				okFood = food;
			}
		}
	}
	if (okFood != NULL) {
		m_pAI->restoreEnergy(okFood->getRestore());
		inventory.remove(okFood);
	} else {
		m_pAI->say("There's nothing to eat!");
	}
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void EatingAction::update(double delta)
{
	if (m_fTimer <= 0) {
		// Need to eat?
		int energyNeeded = m_pAI->getMaxEnergy() - m_pAI->getEnergy();
		if (energyNeeded > 0) {
			m_fTimer = EATING_DURATION;
			eat(energyNeeded);
		} else {
			m_pAI->say("I'm not hungry anymore.");
			stop();
		}
	} else {
		m_fTimer -= delta;
	}
}
