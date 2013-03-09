// -----------------------------------------------------------------
// ERRATIC MOVE BEHAVIOUR
// -----------------------------------------------------------------
#include "ErraticMoveBehaviour.h"
#include "../Physics/MovesHelper.h"
#include "../World/Character.h"

// -----------------------------------------------------------------
// Name : ErraticMoveBehaviour
// -----------------------------------------------------------------
ErraticMoveBehaviour::ErraticMoveBehaviour(Character * ai) : Behaviour(ai)
{
	m_fWait = 0;
}

// -----------------------------------------------------------------
// Name : ~ErraticMoveBehaviour
// -----------------------------------------------------------------
ErraticMoveBehaviour::~ErraticMoveBehaviour()
{
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void ErraticMoveBehaviour::update(double delta)
{
	if (!m_pAI->isMoving()) {
		if (m_fWait <= 0) {
			m_fWait = (rand() % 2) * FRAND100(3);	// 0-3 seconds
			f3d target(1 - FRAND100(2), 1 - FRAND100(2));
			m_pAI->addMovement(MovesHelper::newConstantMove(target, m_pAI->get3DSpeed()));
		} else {
			m_fWait -= delta;
		}
	}
}
