#ifndef _AI_H
#define _AI_H

#include "../World/Character.h"
#include "Behaviour.h"

#define INTERACT_DELAY		0.5f
#define TRAITS_FRIENDLY		"friendly"
#define TRAITS_FUNNY		"funny"
#define TRAITS_AGGRESSIVE	"aggressive"

class AI : public Character
{
public:
	AI(JoS_Element& json);
    virtual ~AI();

    virtual void update(double delta);
    void setBehaviour(Behaviour * pBehaviour) { FREE(m_pBehaviour); m_pBehaviour = pBehaviour; };

    static void initData();
    static void releaseData();
    static float getTraitsRelation(string from, string towards);

private:
    void checkInteractions(list<PartitionableItem*>*);
    void interact(GameObject*);
    float computeObjectiveAttraction(Character * pOther);

    Behaviour * m_pBehaviour;
    double m_fInteractTimer;

    static JoSon * m_pTraitsRelations;
};

#endif
