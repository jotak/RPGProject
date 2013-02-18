#ifndef _GUI_BUTTON_H
#define _GUI_BUTTON_H

#include "guiImage.h"
#include "guiLabel.h"
#include "../Geometries/GeometryQuads.h"
#include "../Input/InputEngine.h"

enum BtnClickOptions
{
    BCO_None = 0,
    BCO_ReplaceTex,
    BCO_AddTex,
    BCO_Decal,
    BCO_Scale,
    BCO_Enlight
};

// must return false if resulting in a closing event
typedef tr1::function<bool (ComponentOwnerInterface*)> ClickCallback;

class guiButton : public guiImage
{
public:
    // Constructor / destructor
    guiButton();
    virtual ~guiButton();

    // Inherited functions
    virtual u32 getType() { return guiComponent::getType() | GOTYPE_BUTTON; };
    virtual void update(double delta);
    virtual void displayAt(int iXOffset, int iYOffset, Color cpntColor, Color docColor);
    virtual void moveTo(int xPxl, int yPxl);
    virtual void moveBy(int xPxl, int yPxl);
    virtual void setEnabled(bool bEnabled);

    // Input functions
    virtual guiObject * onButtonEvent(ButtonAction * pEvent);
    virtual guiObject * onCursorMoveEvent(int xPxl, int yPxl);
    virtual void onCursorMoveOutEvent();

    // Member access functions
    string getText() { return m_pLabel->getText(); };
    void setText(string sText);
    void setFontId(FontId id) { m_pLabel->setFontId(id); };
    void setTextColor(Color textColor) { m_pLabel->setDiffuseColor(textColor); };
    BtnClickOptions getClickOption() { return m_ClickOption; };
    BtnClickOptions getOverOption() { return m_OverOption; };
    void setClickOption(BtnClickOptions clickOption) { m_ClickOption = clickOption; };
    void setOverOption(BtnClickOptions overOption) { m_OverOption = overOption; };
    GeometryQuads * getClickedGeometry() { return m_pGeometryClicked; };
    GeometryQuads * getOverGeometry() { return m_pGeometryOver; };
    GeometryQuads * getNormalGeometry() { return m_pGeometryNormal; };
    void setCatchButton2Events(bool bCatch) { m_bCatchButton2Events = bCatch; };
    void setCatchDoubleClicks(bool bCatch) { m_bCatchDoubleClicks = bCatch; };
    void setMultiClicks(bool bMulti) { m_bMultiClicks = bMulti; };
    void setNormalTexture(Texture * pTex);
    void setClickCallback(ClickCallback clickCallback) { m_ClickCallback = clickCallback; };
    bool doClick(ButtonAction * pEvent);

    // Clone / init
    virtual void init(string sText, FontId fontId, Color textColor, Texture * pClickedTex, BtnClickOptions clickOption, Texture * pOverTex, BtnClickOptions overOption, Texture * pTex, string sCpntId, int xPxl, int yPxl, int wPxl, int hPxl);
    virtual guiObject * clone();

    // Size & position
    virtual void onResize(int iOldWidth, int iOldHeight);
    void autoPad(int margin);
    void autoPadWidth(int margin, int minWidth = 0);

    // Other
    void attachImage(Texture * pTex);

    // Static default constructors
    static guiButton * createDefaultNormalButton(string sText, string sId);
    static guiButton * createDefaultSmallButton(string sText, int width, string sId);
    static guiButton * createDefaultWhiteButton(string sText, int width, int height, string sId);
    static guiButton * createDefaultImageButton(Texture * pTex, string sId);

protected:
    bool m_bMouseDown;
    bool m_bMouseOver;
    guiLabel * m_pLabel;
    BtnClickOptions m_ClickOption;
    BtnClickOptions m_OverOption;
    GeometryQuads * m_pGeometryClicked;
    GeometryQuads * m_pGeometryOver;
    GeometryQuads * m_pGeometryNormal;
    GeometryQuads * m_pGeometryAttachedImage;
    bool m_bClickState;
    bool m_bCatchButton2Events;
    bool m_bCatchDoubleClicks;
    bool m_bMultiClicks;
    float m_fMultiClicksTimer;
    ButtonAction m_MultiClicksEvent;
    ClickCallback m_ClickCallback;
};

#endif
