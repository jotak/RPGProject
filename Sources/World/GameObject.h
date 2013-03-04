#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "../Geometries/Geometry.h"
#include "../Physics/PartitionableItem.h"

class GameObject : public PartitionableItem
{
public:
	GameObject();
    virtual ~GameObject();

    virtual void update(double delta);
    virtual void display();

    void setPosition(f3d pos);
    f3d getPosition() const { return m_pos; };
    Geometry * getGeometry() { return m_pGeometry; };
    void setGeometry(Geometry * pGeo) { m_pGeometry = pGeo; };

private:
    f3d m_pos;
    Geometry * m_pGeometry;
};

#endif
