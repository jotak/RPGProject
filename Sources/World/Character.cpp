// -----------------------------------------------------------------
// CHARACTER
// -----------------------------------------------------------------
#include "Character.h"
#include "../Physics/MovesHelper.h"

// -----------------------------------------------------------------
// Name : Character
// -----------------------------------------------------------------
Character::Character(double speed)
{
	m_pBehaviour = NULL;
	setSpeed(speed);
}

// -----------------------------------------------------------------
// Name : ~Character
// -----------------------------------------------------------------
Character::~Character()
{
	FREE(m_pBehaviour);
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void Character::update(double delta)
{
	if (m_pBehaviour != NULL) {
		m_pBehaviour->update(delta);
	}
	MovingObject::update(delta);
}

// -----------------------------------------------------------------
// Name : setMoveTarget
// -----------------------------------------------------------------
void Character::setMoveTarget(Coords3D pos)
{
	setMovement(MovesHelper::newConstantMove(pos - getPosition(), speed));
}
