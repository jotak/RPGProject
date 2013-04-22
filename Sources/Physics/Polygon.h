#ifndef _POLYGON_H
#define _POLYGON_H

#include "../Utils/utils.h"

typedef tuple<f3d, double> point_and_distance;

class Polygon
{
public:
	static Polygon * builder() { return new Polygon(); };
    Polygon * addPoint(f3d point) { vertice.push_back(point); return this; };
    bool isInside(f3d point) { return false; };
    point_and_distance closestDistanceTo(f3d point) { return point_and_distance(f3d(), 0.0f); };

private:
	Polygon() {};
    list<f3d> vertice;
};

#endif
