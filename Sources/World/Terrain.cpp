// -----------------------------------------------------------------
// TERRAIN
// -----------------------------------------------------------------
#include "Terrain.h"
#include "../Display/DisplayEngine.h"

// -----------------------------------------------------------------
// Name : Terrain
// -----------------------------------------------------------------
Terrain::Terrain()
{
}

// -----------------------------------------------------------------
// Name : ~Terrain
// -----------------------------------------------------------------
Terrain::~Terrain()
{
	FREEVEC(m_pGeometries);
}

// -----------------------------------------------------------------
// Name : display
// -----------------------------------------------------------------
void Terrain::display()
{
	for (Geometry* &pGeo : m_pGeometries) {
		pGeo->display(Coords3D(0, 0, BOARDPLANE), Color::white);
	}
}
