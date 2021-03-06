#ifndef _GUI_FRAME_MOUSE_FOCUS_H
#define _GUI_FRAME_MOUSE_FOCUS_H

#include "guiFrameEffect.h"

class guiFrameMouseFocus : public guiFrameEffect
{
public:
    guiFrameMouseFocus(u16 uEffectId, float fFadeOutTime);
    virtual ~guiFrameMouseFocus();

    virtual void onBeginDisplay(int iXOffset, int iYOffset, Color * cpntColor, Color * docColor);
    virtual void onEndDisplay();
    virtual void onUpdate(double delta);
    virtual void reset();
    virtual guiFrameMouseFocus * clone();

protected:
    float m_fTimer, m_fTotalTime;
};

#endif
