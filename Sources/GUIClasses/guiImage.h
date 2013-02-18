#ifndef _GUI_IMAGE_H
#define _GUI_IMAGE_H

#include "guiComponent.h"

class guiImage : public guiComponent
{
public:
    // Constructor / destructor
    guiImage();
    virtual ~guiImage();

    // Inherited functions
    virtual void displayAt(int iXOffset, int iYOffset, Color cpntColor, Color docColor);

    // Size and position
    virtual void onResize(int iOldWidth, int iOldHeight);

    // Clone / init
    virtual void init(Texture * pTex, string sCpntId, int xPxl, int yPxl, int wPxl, int hPxl);
    virtual guiObject * clone();

    // Misc.
    void setCatchClicks(bool b) { m_bCatchClicks = b; };
    virtual guiObject * onButtonEvent(ButtonAction * pEvent);
    Texture * getImageTexture();
    void setImageTexture(Texture * pTex);

protected:
    bool m_bCatchClicks;
};

#endif
