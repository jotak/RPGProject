#ifndef _IDLE_ACTION_H
#define _IDLE_ACTION_H

#include "../AI.h"

class Discussion;

class IdleAction
{
public:
    static void idle(AI*);

private:
    static void startDiscussion(AI*, JoS_Element&, list<AI*>&);
    static void joinDiscussion(AI*, Discussion*);
};

#endif
