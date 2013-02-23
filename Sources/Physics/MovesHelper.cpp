// -----------------------------------------------------------------
// MovesHelper
// -----------------------------------------------------------------
#include "MovesHelper.h"
#include "FunctionalMove.h"
#include "../Utils/utils.h"

// -----------------------------------------------------------------
// Name : newConstantMove
//	Use identity function
// -----------------------------------------------------------------
Movement * MovesHelper::newConstantMove(Coords3D vector, double fSpeed)
{
	return new FunctionalMove(vector, fSpeed, [](double in) -> double { return in; });
}

// -----------------------------------------------------------------
// Name : newDecelMove
//	Use cosinus function in [0, PI/2[ for deceleration
// -----------------------------------------------------------------
Movement * MovesHelper::newDecelMove(Coords3D vector, double fFullSpeed)
{
	return new FunctionalMove(vector, fFullSpeed, [](double in) -> double { return cos(PI * in / 2.0f); });
}

// -----------------------------------------------------------------
// Name : newAccelMove
//	Use sinus function in [0, PI/2[ for acceleration
// -----------------------------------------------------------------
Movement * MovesHelper::newAccelMove(Coords3D vector, double fFullSpeed)
{
	return new FunctionalMove(vector, fFullSpeed, [](double in) -> double { return sin(PI * in / 2.0f); });
}

// -----------------------------------------------------------------
// Name : newAccelDecelMove
//	Use sinus function in [0, PI[ for acceleration follwed by deceleration
// -----------------------------------------------------------------
Movement * MovesHelper::newAccelDecelMove(Coords3D vector, double fFullSpeed)
{
	return new FunctionalMove(vector, fFullSpeed, [](double in) -> double { return sin(PI * in); });
}

