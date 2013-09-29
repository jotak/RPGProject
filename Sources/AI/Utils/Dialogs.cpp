// -----------------------------------------------------------------
// Common dialogs
// -----------------------------------------------------------------
#include "Dialogs.h"
#include "../../Managers/DebugManager.h"

Dialogs * Dialogs::m_pInstance = NULL;

// -----------------------------------------------------------------
// Name : Dialogs
// -----------------------------------------------------------------
Dialogs::Dialogs()
{
	idleDialogs = loadJson("idle.json");
	buyerDialogs = loadJson("buyer.json");
}

// -----------------------------------------------------------------
// Name : ~Dialogs
// -----------------------------------------------------------------
Dialogs::~Dialogs()
{
	delete idleDialogs;
	delete buyerDialogs;
}

// -----------------------------------------------------------------
// Name : loadJson
// -----------------------------------------------------------------
JoSon * Dialogs::loadJson(string path)
{
    // Build file name
    string jsonDesc = string(DIALOGS_PATH) + path;
    string err;
    JoSon * json = JoSon::fromFile(jsonDesc, &err);
    if (json == NULL) {
    	_debug->error(err);
    }
    return json;
}
