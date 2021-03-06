#include "guiFrameMouseFocus.h"
#include "../guiFrame.h"

// -----------------------------------------------------------------
// Name : guiFrameMouseFocus
//  Constructor
// -----------------------------------------------------------------
guiFrameMouseFocus::guiFrameMouseFocus(u16 uEffectId, float fFadeOutTime) : guiFrameEffect(uEffectId)
{
    m_fTimer = m_fTotalTime = fFadeOutTime;
}

// -----------------------------------------------------------------
// Name : ~guiFrameMouseFocus
//  Destructor
// -----------------------------------------------------------------
guiFrameMouseFocus::~guiFrameMouseFocus()
{
}

// -----------------------------------------------------------------
// Name : onBeginDisplay
// -----------------------------------------------------------------
void guiFrameMouseFocus::onBeginDisplay(int iXOffset, int iYOffset, Color * cpntColor, Color * docColor)
{
    if (!m_pFrame->isEnabled()) {
        return;
    }
    // Fading
    Color color(1, 1, 1, 0.4f + 0.6f * m_fTimer / m_fTotalTime);
    docColor->multiply(&color);
}

// -----------------------------------------------------------------
// Name : onEndDisplay
// -----------------------------------------------------------------
void guiFrameMouseFocus::onEndDisplay()
{
}

// -----------------------------------------------------------------
// Name : onUpdate
// -----------------------------------------------------------------
void guiFrameMouseFocus::onUpdate(double delta)
{
//  if (!m_pFrame->isFocused())
//  {
    if (m_pFrame->isPointed())
    {
        m_fTimer += delta;
        if (m_fTimer > m_fTotalTime)
            m_fTimer = m_fTotalTime;
    }
    else
    {
        m_fTimer -= delta;
        if (m_fTimer < 0)
            m_fTimer = 0;
    }
//  }
}

// -----------------------------------------------------------------
// Name : clone
// -----------------------------------------------------------------
guiFrameMouseFocus * guiFrameMouseFocus::clone()
{
    guiFrameMouseFocus * pClone = new guiFrameMouseFocus(m_uEffectId, m_fTotalTime);
    return pClone;
}

// -----------------------------------------------------------------
// Name : reset
// -----------------------------------------------------------------
void guiFrameMouseFocus::reset()
{
    guiFrameEffect::reset();
    m_fTimer = m_fTotalTime;
}
