#include "guiImage.h"
#include "../Geometries/GeometryQuads.h"
#include "ComponentOwnerInterface.h"
#include "../Display/TextureEngine.h"
#include "../Display/DisplayEngine.h"
#include "../Input/InputEngine.h"

// -----------------------------------------------------------------
// Name : guiImage
//  Constructor
// -----------------------------------------------------------------
guiImage::guiImage() : guiComponent()
{
    m_iWidth = m_iHeight = -1;
    m_bCatchClicks = false;
}

// -----------------------------------------------------------------
// Name : ~guiImage
//  Destructor
// -----------------------------------------------------------------
guiImage::~guiImage()
{
}

// -----------------------------------------------------------------
// Name : init
// -----------------------------------------------------------------
void guiImage::init(Texture * pTex, string sCpntId, int xPxl, int yPxl, int wPxl, int hPxl)
{
    guiComponent::init(sCpntId, xPxl, yPxl, wPxl, hPxl);
    if (m_iWidth < 0) {
    	m_iWidth = pTex->getWidth();
    }
    if (m_iHeight < 0) {
    	m_iHeight = pTex->getHeight();
    }
    QuadData quad(0, m_iWidth, 0, m_iHeight, pTex);
    m_pGeometry = new GeometryQuads(&quad, VB_Static);
}

// -----------------------------------------------------------------
// Name : clone
// -----------------------------------------------------------------
guiObject * guiImage::clone()
{
    guiImage * pObj = new guiImage();
    pObj->init(((GeometryQuads*)m_pGeometry)->getTexture(), m_sCpntId, m_iXPxl, m_iYPxl, m_iWidth, m_iHeight);
    return pObj;
}

// -----------------------------------------------------------------
// Name : displayAt
// -----------------------------------------------------------------
void guiImage::displayAt(int iXOffset, int iYOffset, Color cpntColor, Color docColor)
{
    if (!m_bVisible) {
        return;
    }
    CoordsScreen coords = CoordsScreen(m_iXPxl + iXOffset, m_iYPxl + iYOffset, GUIPLANE);
    m_pGeometry->display(coords, cpntColor * m_DiffuseColor);
}

// -----------------------------------------------------------------
// Name : onResize
// -----------------------------------------------------------------
void guiImage::onResize(int iOldWidth, int iOldHeight)
{
    guiComponent::onResize(iOldWidth, iOldHeight);
    if (iOldWidth == m_iWidth && iOldHeight == m_iHeight) {
        return;
    }
    if (m_pGeometry != NULL)
    {
        QuadData quad(0, m_iWidth, 0, m_iHeight, ((GeometryQuads*)m_pGeometry)->getTexture());
        ((GeometryQuads*)m_pGeometry)->modify(&quad);
    }
}

// -----------------------------------------------------------------
// Name : onButtonEvent
// -----------------------------------------------------------------
guiObject * guiImage::onButtonEvent(ButtonAction * pEvent)
{
    if (pEvent->eButton != Button1 || /*pEvent->eEvent != Event_Down || */!m_bEnabled || !m_bVisible || !m_bCatchClicks) {
        return NULL;
    }
    m_pOwner->onButtonEvent(pEvent, this);
    return this;
}

// -----------------------------------------------------------------
// Name : getImageTexture
// -----------------------------------------------------------------
Texture * guiImage::getImageTexture()
{
    if (m_pGeometry) {
        return ((GeometryQuads*)m_pGeometry)->getTexture();
    }
    return NULL;
}

// -----------------------------------------------------------------
// Name : setImageTexture
// -----------------------------------------------------------------
void guiImage::setImageTexture(Texture * pTex)
{
    if (m_pGeometry) {
        ((GeometryQuads*)m_pGeometry)->setTexture(pTex);
    }
}
