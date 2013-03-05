#ifndef _AI_H
#define _AI_H

#include "../World/Character.h"
#include "Behaviour.h"

class AI : public Character
{
public:
	AI(JoS_Element& json);
    virtual ~AI();

    virtual void update(double delta);

    void setBehaviour(Behaviour * pBehaviour) { FREE(m_pBehaviour); m_pBehaviour = pBehaviour; };

private:
    void checkInteractions(list<PartitionableItem*>*);
    void interact(GameObject*);

    Behaviour * m_pBehaviour;
};

#endif
