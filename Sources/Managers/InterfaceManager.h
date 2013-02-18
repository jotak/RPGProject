#ifndef _INTERFACEMANAGER_H
#define _INTERFACEMANAGER_H

#include "../GUIClasses/guiPopup.h"
#include "../Input/EventListener.h"

#define SMALL_ICON_SIZE       32
#define SMALL_ICON_SPACING    4

class InterfaceManager : public EventListener
{
public:
    class TopDisplayObject : public BaseObject
    {
    public:
    	void display() {
    		pObj->displayAt(iX, iY, *cpntColor, *docColor);
    	};
        guiComponent * pObj;
        int iX, iY;
        Color * cpntColor;
        Color * docColor;
    };

    // Singleton / destructor
    ~InterfaceManager();
    static InterfaceManager * getInstance()
    {
        if (m_pInstance == NULL) m_pInstance = new InterfaceManager();
        return m_pInstance;
    };

    // Manager functions
    void init();
    void initMenu();
    void update(double delta);
    void display();

    // Input functions
    bool onCatchButtonEvent(ButtonAction * pEvent);
    bool onCursorMoveEvent(int xPxl, int yPxl);

    // Frame management
    void registerFrame(guiFrame * pFrm);
    guiFrame * findFrame(string frmId);
    guiFrame * findFrameFromDoc(guiDocument * pDoc);
    void deleteFrame(guiFrame * pFrm);
    guiFrame * deleteCurrentFrame(list<guiFrame*>::iterator it);
    void bringFrameAbove(guiFrame * pFrm);
    guiComponent * getObjectAt(int xPxl, int yPxl, int * xoffset, int * yoffset);

    void topDisplay(guiComponent * pObj, int iX, int iY, Color * cpntColor, Color * docColor);
    void cancelTopDisplay(guiComponent * pObj);
    void onResize(int oldw, int oldh);
    bool onClickStart();
    void resetSharedPointers(guiObject * pObj = NULL);
    void getRichText(guiDocument * pDest, CoordsScreen offset, string sSource);

    void setUniqueDialog(guiDocument * pDoc);

private:
    InterfaceManager();
    static InterfaceManager * m_pInstance;

    void deleteAllFrames();

    list<guiFrame*> m_pFrameList;

    guiPopup * m_pTooltip;
    float m_fTooltipTime;
    BaseObject * m_pTargetedObject;
    guiObject * m_pClickedObjects[2];
    guiObject * m_pPointedObject;
    list<TopDisplayObject*> m_pTopDisplayList;
};

// Helper alias
#define _interface InterfaceManager::getInstance()

#endif
