#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "../Geometries/Geometry.h"

class GameObject
{
public:
	GameObject();
    virtual ~GameObject();

    virtual void update(double delta);
    virtual void display();

    void setPosition(double x, double y, double z) { m_pos.x = x; m_pos.y = y; m_pos.z = z; };
    Geometry * getGeometry() { return m_pGeometry; };
    void setGeometry(Geometry * pGeo) { m_pGeometry = pGeo; };

protected:
    Coords3D m_pos;
    Geometry * m_pGeometry;
};

#endif
