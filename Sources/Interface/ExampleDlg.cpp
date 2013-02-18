#include "ExampleDlg.h"
#include "../Data/LocalisationTool.h"
#include "../Display/TextureEngine.h"
#include "../GUIClasses/guiLabel.h"
#include "../GUIClasses/guiButton.h"

// -----------------------------------------------------------------
// Name : ExampleDlg
//  Constructor
// -----------------------------------------------------------------
ExampleDlg::ExampleDlg() : guiDocument()
{
	m_pFrame = NULL;
	build();
}

// -----------------------------------------------------------------
// Name : ~ExampleDlg
//  Destructor
// -----------------------------------------------------------------
ExampleDlg::~ExampleDlg()
{
}

// -----------------------------------------------------------------
// Name : onClickMyButton + callback
// -----------------------------------------------------------------
bool onClickButton(ComponentOwnerInterface * pDoc) { return ((ExampleDlg*)pDoc)->onClickMyButton(); }
bool ExampleDlg::onClickMyButton()
{
	guiComponent * pCpnt = getComponent("testButton");
	if (pCpnt != NULL) {
		pCpnt->moveTo(rand() % 230, rand() % 410);
	}
	return true; // should have returned false if the object was going to be destroyed (like for instance when closing the window)
}

// -----------------------------------------------------------------
// Name : build
// -----------------------------------------------------------------
void ExampleDlg::build()
{
	string title = i18n->getText("Example title");
    guiDocument::init(
    		title,
    		_tex->findTexture("gui/interface:WinBg"),
    		0/*x*/,
    		0/*y*/,
    		100,
    		100);

    m_pFrame = guiFrame::createDefaultFrame(FB_FitDocumentToFrame, FB_FitDocumentToFrame, 350, 450, true, title);
    m_pFrame->centerOnScreen();
    m_pFrame->setDocument(this);

    // Objects on document
    guiLabel * pLabel = guiLabel::createDefaultLabel(
    		i18n->getText("Example text"),
    		"testLabel",
    		0/*x*/,
    		40/*y*/);
    pLabel->hCenterOn(this);
    addComponent(pLabel);

    guiButton * pBtn = guiButton::createDefaultNormalButton(
    		i18n->getText("Example button"),
    		"testButton");
    pBtn->setDimensions(120, 40);
    pBtn->setYPos(80);
    pBtn->hCenterOn(this);
    pBtn->setTooltipText(i18n->getText("Example tooltip"));
    pBtn->setClickCallback(onClickButton);
    addComponent(pBtn);
}
