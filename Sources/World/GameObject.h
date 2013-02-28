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
    f3d getPosition() { return m_pos; };
    Geometry * getGeometry() { return m_pGeometry; };
    void setGeometry(Geometry * pGeo) { m_pGeometry = pGeo; };

protected:
    f3d m_pos;
    Geometry * m_pGeometry;
};

#endif
