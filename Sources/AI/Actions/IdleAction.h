#ifndef _IDLE_ACTION_H
#define _IDLE_ACTION_H

#include "../../Utils/utils.h"
#include "../../Data/JoSon/JoSon.h"

class Discussion;
class AI;

class IdleAction
{
public:
    static void idle(AI*);

private:
    static void startDiscussion(AI*, JoS_Element&, vector<AI*>&);
    static void joinDiscussion(AI*, Discussion*);
};

#endif
