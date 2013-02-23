// -----------------------------------------------------------------
// MOVING OBJECT
// -----------------------------------------------------------------
#include "MovingObject.h"

// -----------------------------------------------------------------
// Name : MovingObject
// -----------------------------------------------------------------
MovingObject::MovingObject()
{
}

// -----------------------------------------------------------------
// Name : ~MovingObject
// -----------------------------------------------------------------
MovingObject::~MovingObject()
{
	FREEVEC(m_Movements);
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void MovingObject::update(double delta)
{
	GameObject::update(delta);
	for (list<Movement*>::iterator it = m_Movements.begin(); it != m_Movements.end(); ++it) {
		m_pos = (*it)->apply(delta, m_pos);
		if ((*it)->getState() == Finished) {
			delete *it;
			it = m_Movements.erase(it);
		}
	}
}
