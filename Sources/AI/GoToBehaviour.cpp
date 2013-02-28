// -----------------------------------------------------------------
// GOTO BEHAVIOUR
// -----------------------------------------------------------------
#include "GoToBehaviour.h"
#include "../Physics/MovesHelper.h"
#include "../World/Character.h"

// -----------------------------------------------------------------
// Name : GoToBehaviour
// -----------------------------------------------------------------
GoToBehaviour::GoToBehaviour(f3d target, Character * ai) : Behaviour(ai)
{
	m_Target = target;
	m_pAI->addMovement(MovesHelper::newConstantMove(target - m_pAI->getPosition(), m_pAI->getSpeed()));
}

// -----------------------------------------------------------------
// Name : ~GoToBehaviour
// -----------------------------------------------------------------
GoToBehaviour::~GoToBehaviour()
{
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void GoToBehaviour::update(double delta)
{
}
