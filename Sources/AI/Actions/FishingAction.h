#ifndef _FISHING_ACTION_H
#define _FISHING_ACTION_H

#include "AIAction.h"
#include "../../World/WaterArea.h"

class FishingAction : public AIAction
{
public:
	FishingAction(AI * ai);
    virtual ~FishingAction();

    virtual void update(double delta);
    virtual bool isFinished() { return AIAction::isFinished() || pFishingArea == NULL; };

private:
    void fish();

    WaterArea * pFishingArea;
    double m_fWait;
};

#endif
