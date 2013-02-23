#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "../Geometries/Geometry.h"

class Terrain
{
public:
	Terrain();
    ~Terrain();

    void display();
    void addGeometry(Geometry * pGeometry) { m_pGeometries.push_back(pGeometry); };

private:
    list<Geometry*> m_pGeometries;
};

#endif
