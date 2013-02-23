#include "guiDocument.h"
#include "guiToggleButton.h"
#include "guiContainer.h"
#include "../Geometries/GeometryQuads.h"
#include "../Data/LocalisationTool.h"
#include "../Display/DisplayEngine.h"

// -----------------------------------------------------------------
// Name : guiDocument
//  Constructor
// -----------------------------------------------------------------
guiDocument::guiDocument()
{
    m_pFocusedComponent = NULL;
    m_bNeedDestroy = false;
    m_bContentChanged = false;
    m_bEnabled = true;
    m_sTitle = "";
    m_pOwner = NULL;
}

// -----------------------------------------------------------------
// Name : ~guiDocument
//  Destructor
// -----------------------------------------------------------------
guiDocument::~guiDocument()
{
    FREEVEC(m_pComponentsList);
}

// -----------------------------------------------------------------
// Name : init
// -----------------------------------------------------------------
void guiDocument::init(string sTitle, Texture * pTex, int xPxl, int yPxl, int wPxl, int hPxl)
{
    guiObject::init(xPxl, yPxl, wPxl, hPxl);
    m_sTitle = sTitle;

    QuadData quad(0, m_iWidth, 0, m_iHeight, pTex);
    m_pGeometry = new GeometryQuads(&quad, VB_Static);
    onLoad();
}

// -----------------------------------------------------------------
// Name : clone
// -----------------------------------------------------------------
guiObject * guiDocument::clone()
{
    guiDocument * pDoc = new guiDocument();
    pDoc->init(m_sTitle, ((GeometryQuads*)m_pGeometry)->getTexture(), m_iXPxl, m_iYPxl, m_iWidth, m_iHeight);
    return pDoc;
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void guiDocument::update(double delta)
{
    if (!m_bEnabled) {
        return;
    }
    for (list<guiComponent*>::iterator it = m_pComponentsList.begin(); it != m_pComponentsList.end(); ++it) {
        (*it)->update(delta);
    }
}

// -----------------------------------------------------------------
// Name : displayAt
// -----------------------------------------------------------------
void guiDocument::displayAt(int iXOffset, int iYOffset, Color cpntColor, Color docColor)
{
    // Display document background
    CoordsScreen coords = CoordsScreen(m_iXPxl + iXOffset, m_iYPxl + iYOffset, GUIPLANE);
    m_pGeometry->display(coords, docColor);

    // Display components
    for (list<guiComponent*>::iterator it = m_pComponentsList.begin(); it != m_pComponentsList.end(); ++it) {
    	(*it)->displayAt(m_iXPxl + iXOffset, m_iYPxl + iYOffset, cpntColor, docColor);
    }
    m_bContentChanged = false;
}

// -----------------------------------------------------------------
// Name : getComponentAt
// -----------------------------------------------------------------
guiComponent * guiDocument::getComponentAt(int xPxl, int yPxl)
{
    for (list<guiComponent*>::reverse_iterator it = m_pComponentsList.rbegin(); it != m_pComponentsList.rend(); ++it) {
        if ((*it)->isAt(xPxl, yPxl)) {
            return *it;
        }
    }
    return NULL;
}

// -----------------------------------------------------------------
// Name : onButtonEvent
// -----------------------------------------------------------------
guiObject * guiDocument::onButtonEvent(ButtonAction * pEvent)
{
    if (!m_bEnabled) {
        return NULL;
    }

    if (pEvent->eEvent == Event_Down) {
        guiComponent * cpnt = getComponentAt(pEvent->xPos - pEvent->xOffset, pEvent->yPos - pEvent->yOffset);
        if (cpnt != m_pFocusedComponent && pEvent->eButton == Button1) {
            setFocusedComponent(cpnt);
        }
        if (cpnt != NULL) {
            guiObject * pObj = cpnt->onButtonEvent(pEvent);
            if (pObj != NULL) {
                return pObj;
            }
        }
        if (pEvent->eButton == Button2) {
            return this;  // Drag (=scroll) document
        }
    } else if (pEvent->eEvent == Event_Drag) {
        moveBy(pEvent->xPos - pEvent->xPosInit, pEvent->yPos - pEvent->yPosInit);
        m_pOwner->checkDocumentPosition();
        return this;
    }

    return NULL;
}

// -----------------------------------------------------------------
// Name : onCursorMoveEvent
// -----------------------------------------------------------------
guiObject * guiDocument::onCursorMoveEvent(int xPxl, int yPxl)
{
    guiComponent * cpnt = getComponentAt(xPxl, yPxl);
    if (cpnt != NULL) {
        return cpnt->onCursorMoveEvent(xPxl, yPxl);
    } else {
        return this;
    }
}

// -----------------------------------------------------------------
// Name : onResize
// -----------------------------------------------------------------
void guiDocument::onResize(int iOldWidth, int iOldHeight)
{
    guiObject::onResize(iOldWidth, iOldHeight);
    if (m_iWidth == iOldWidth && m_iHeight == iOldHeight) {
        return;
    }
    if (m_pGeometry != NULL) {
        QuadData quad(0, m_iWidth, 0, m_iHeight, ((GeometryQuads*)m_pGeometry)->getTexture());
        ((GeometryQuads*)m_pGeometry)->modify(&quad);
    }
}

// -----------------------------------------------------------------
// Name : setFocusedComponent
// -----------------------------------------------------------------
void guiDocument::setFocusedComponent(guiComponent * pCpnt)
{
    if (m_pFocusedComponent != NULL) {
        m_pFocusedComponent->onFocusLost();
    }
    m_pFocusedComponent = pCpnt;
}

// -----------------------------------------------------------------
// Name : setTitleId
// -----------------------------------------------------------------
void guiDocument::setTitleId(string sTitleId)
{
	m_sTitle = i18n->getTextUCFirst(sTitleId);
}

// -----------------------------------------------------------------
// Name : getComponent
// -----------------------------------------------------------------
guiComponent * guiDocument::getComponent(string cpntId)
{
    for (list<guiComponent*>::iterator it = m_pComponentsList.begin(); it != m_pComponentsList.end(); ++it) {
    	if (cpntId == (*it)->getId()) {
    		return *it;
    	}
    }
    return NULL;
}

// -----------------------------------------------------------------
// Name : deleteAllComponents
// -----------------------------------------------------------------
void guiDocument::deleteAllComponents()
{
    FREEVEC(m_pComponentsList);
    m_pFocusedComponent = NULL;
    m_bContentChanged = true;
}

// -----------------------------------------------------------------
// Name : deleteComponent
// -----------------------------------------------------------------
bool guiDocument::deleteComponent(guiComponent * pCpnt)
{
    for (list<guiComponent*>::iterator it = m_pComponentsList.begin(); it != m_pComponentsList.end(); ++it) {
    	if (pCpnt == *it) {
    		m_pComponentsList.erase(it);
            if (m_pFocusedComponent == pCpnt) {
            	m_pFocusedComponent = NULL;
            }
            m_bContentChanged = true;
    		delete pCpnt;
    		return true;
    	}
    }
    return false;
}

// -----------------------------------------------------------------
// Name : removeCurrentComponent
// -----------------------------------------------------------------
guiComponent * guiDocument::removeCurrentComponent(list<guiComponent*>::iterator * it)
{
	guiComponent * toDelete = **it;
    if (m_pFocusedComponent == toDelete) {
        m_pFocusedComponent = NULL;
    }
    m_bContentChanged = true;
    *it = m_pComponentsList.erase(*it);
    return toDelete;
}

// -----------------------------------------------------------------
// Name : addComponent
// -----------------------------------------------------------------
void guiDocument::addComponent(guiComponent * cpnt)
{
    m_pComponentsList.push_back(cpnt);
    if (cpnt->getOwner() == NULL) {
        cpnt->setOwner(this);
    }
}

// -----------------------------------------------------------------
// Name : bringAbove
// -----------------------------------------------------------------
void guiDocument::bringAbove(guiComponent * cpnt)
{
	m_pComponentsList.remove(cpnt);
	m_pComponentsList.push_front(cpnt);
}

// -----------------------------------------------------------------
// Name : doClick
// -----------------------------------------------------------------
void guiDocument::doClick(string sCpntId)
{
    guiComponent * pCpnt = getComponent(sCpntId);
    if (pCpnt == NULL || !pCpnt->isVisible() || !pCpnt->isEnabled()) {
        return;
    }
    ButtonAction action;
    action.eButton = Button1;
    action.eEvent = Event_Down;
    action.xOffset = action.yOffset = 0;
    action.xPos = action.xPosInit = pCpnt->getXPos() + 1;
    action.yPos = action.yPosInit = pCpnt->getYPos() + 1;
    pCpnt->onButtonEvent(&action);
    action.eEvent = Event_Up;
    pCpnt->onButtonEvent(&action);
}
