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
    void setDimensions(double left, double right, double top, double bottom);
    f3d getTopLeft() { return m_TopLeft; };
    f3d getDimensions() { return m_Dimensions; };

private:
    list<Geometry*> m_pGeometries;
    f3d m_TopLeft, m_Dimensions;
};

#endif
