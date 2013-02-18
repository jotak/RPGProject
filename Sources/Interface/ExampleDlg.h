#ifndef _EXAMPLE_DLG_H
#define _EXAMPLE_DLG_H

#include "../GUIClasses/guiDocument.h"
#include "../GUIClasses/guiFrame.h"

class ExampleDlg : public guiDocument
{
public:
	ExampleDlg();
	~ExampleDlg();

	guiFrame * getFrame() { return m_pFrame; };
	bool onClickMyButton();

private:
	void build();

	guiFrame * m_pFrame;
};

#endif
