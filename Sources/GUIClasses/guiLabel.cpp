#include "guiLabel.h"
#include "../Geometries/GeometryText.h"
#include "ComponentOwnerInterface.h"
#include "../Display/DisplayEngine.h"
#include "../Fonts/FontEngine.h"
#include "../Input/InputEngine.h"

// -----------------------------------------------------------------
// Name : guiLabel
//  Constructor
// -----------------------------------------------------------------
guiLabel::guiLabel() : guiComponent()
{
    m_sText = "";
    m_FontId = (FontId)0;
    m_iBoxWidth = 0;
    m_bCatchClicks = false;
    m_pComponentOwner = NULL;
}

// -----------------------------------------------------------------
// Name : ~guiLabel
//  Destructor
// -----------------------------------------------------------------
guiLabel::~guiLabel()
{
}

// -----------------------------------------------------------------
// Name : init
// -----------------------------------------------------------------
void guiLabel::init(string sText, FontId fontId, Color textColor, string sCpntId, int xPxl, int yPxl, int wPxl, int hPxl)
{
    guiComponent::init(sCpntId, xPxl, yPxl, wPxl, hPxl);
    m_FontId = fontId;
    setDiffuseColor(textColor);
    m_iBoxWidth = wPxl;
    m_sText = sText;
    computeGeometry();
}

// -----------------------------------------------------------------
// Name : clone
// -----------------------------------------------------------------
guiObject * guiLabel::clone()
{
    guiLabel * pObj = new guiLabel();
    pObj->init(m_sText, m_FontId, getDiffuseColor(), m_sCpntId, m_iXPxl, m_iYPxl, m_iBoxWidth, m_iHeight);
    return pObj;
}

// -----------------------------------------------------------------
// Name : displayAt
// -----------------------------------------------------------------
void guiLabel::displayAt(int iXOffset, int iYOffset, Color cpntColor, Color docColor)
{
    if (!m_bVisible) {
        return;
    }
    CoordsScreen coords = CoordsScreen(m_iXPxl + iXOffset, m_iYPxl + iYOffset, GUIPLANE);
    m_pGeometry->display(coords, cpntColor * m_DiffuseColor);
}

// -----------------------------------------------------------------
// Name : setText
// -----------------------------------------------------------------
void guiLabel::setText(string sText)
{
    if (sText == m_sText) {
        return;
    }
    m_sText = sText;
    computeGeometry();
}

// -----------------------------------------------------------------
// Name : setBoxWidth
// -----------------------------------------------------------------
void guiLabel::setBoxWidth(int iWidth)
{
    m_iBoxWidth = iWidth;
    computeGeometry();
}

// -----------------------------------------------------------------
// Name : computeGeometry
// -----------------------------------------------------------------
void guiLabel::computeGeometry()
{
    if (m_iBoxWidth > 0) {
        setHeight(_font->putStringInBox(m_sText, m_iBoxWidth, m_aiAllFonts[(int)m_FontId]));
        setWidth(_font->getStringLength(m_sText, m_aiAllFonts[(int)m_FontId]));
    } else {
        setWidth(_font->getStringLength(m_sText, m_aiAllFonts[(int)m_FontId]));
        setHeight(_font->getStringHeight(m_sText, m_aiAllFonts[(int)m_FontId]));
    }
    if (m_pGeometry != NULL) {
        ((GeometryText*)m_pGeometry)->setText(m_sText, m_aiAllFonts[(int)m_FontId]);
    } else {
        m_pGeometry = new GeometryText(m_sText, m_aiAllFonts[(int)m_FontId], VB_Static);
    }
}

// -----------------------------------------------------------------
// Name : onButtonEvent
// -----------------------------------------------------------------
guiObject * guiLabel::onButtonEvent(ButtonAction * pEvent)
{
    if (!m_bEnabled || !m_bVisible || !m_bCatchClicks) {
        return NULL;
    }
    if (m_pComponentOwner != NULL)
    {
        m_pComponentOwner->onButtonEvent(pEvent);
        return this;
    }
    if (pEvent->eButton != Button1 || pEvent->eEvent != Event_Down || !m_bEnabled || !m_bVisible || !m_bCatchClicks) {
        return NULL;
    }
    m_pOwner->onButtonEvent(pEvent, this);
    return this;
}

// -----------------------------------------------------------------
// Name : createDefaultLabel
//  Static default constructor
// -----------------------------------------------------------------
guiLabel * guiLabel::createDefaultLabel(string sText, string sId)
{
    guiLabel * pLbl = new guiLabel();
    pLbl->init(
    		sText,
    		TEXT_FONT,
    		TEXT_COLOR,
    		sId,
    		0/*x*/,
    		0/*y*/,
    		-1/*w - it will be computed automatically*/,
    		-1/*h - it will be computed automatically*/);
    return pLbl;
}

// -----------------------------------------------------------------
// Name : createDefaultLabel
//  Static default constructor
// -----------------------------------------------------------------
guiLabel * guiLabel::createDefaultLabel(string sText, string sId, int xPxl, int yPxl)
{
	guiLabel * pLbl = createDefaultLabel(sText, sId);
	pLbl->setXPos(xPxl);
	pLbl->setYPos(yPxl);
	return pLbl;
}
