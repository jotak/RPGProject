#include "DisplayEngine.h"
#include "TextureEngine.h"
#include "../Geometries/Geometry.h"
#include "../Managers/DebugManager.h"
#include "../Data/Parameters.h"

#define BASE_WIDTH    1024.0f
#define BASE_HEIGHT   576.0f

DisplayEngine * DisplayEngine::m_pInstance = NULL;

// ------------------------------------------------------------------
// Name : DisplayEngine
//  Constructor
// ------------------------------------------------------------------
DisplayEngine::DisplayEngine()
{
    m_ModeState = DMS_Undefined;
    m_bReady = false;
    m_iStencilState = 0;
    m_iWindow = -1;
    m_bAdditive = false;
    m_iStencilDepth = 0;
    m_dScreenRatio = 1;
    m_bIgnoreNextResize = false;
}

// ------------------------------------------------------------------
// Name : ~DisplayEngine
//  Destructor
// ------------------------------------------------------------------
DisplayEngine::~DisplayEngine()
{
	// Everything must have been deleted using Geometry::~Geometry, which calls DisplayEngine::unregisterGeometry
	assert(m_pRegisteredGeometries.empty());
}

// ------------------------------------------------------------------
// Name : init
// ------------------------------------------------------------------
void DisplayEngine::init()
{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_ALPHA);
    m_f3CamPos = Coords3D(0.0f, 0.0f, 0.0f);

    initGlutWindow();
}

// ------------------------------------------------------------------
// Name : initGlutWindow
// ------------------------------------------------------------------
void DisplayEngine::initGlutWindow()
{
	m_bIgnoreNextResize = true;

    if (m_iWindow == -2) {  // was fullscreen
        glutLeaveGameMode();
    } else if (m_iWindow >= 0) {  // was windowed
    	_params->setWinXPos(glutGet(GLUT_WINDOW_X));
    	_params->setWinYPos(glutGet(GLUT_WINDOW_Y));
        glutDestroyWindow(m_iWindow);
    }

    if (_params->isFullscreen())
    {
        glutGameModeString(_params->getGameModeString().c_str());
        glutEnterGameMode();
        _params->setScreenXSize(glutGameModeGet(GLUT_GAME_MODE_WIDTH));
        _params->setScreenYSize(glutGameModeGet(GLUT_GAME_MODE_HEIGHT));
        m_iWindow = -2;
    }
    else
    {
        glutInitWindowPosition(_params->getWinXPos(), _params->getWinYPos());
        _params->setScreenXSize(_params->getWinWidth());
        _params->setScreenYSize(_params->getWinHeight());
        glutInitWindowSize(_params->getScreenXSize(), _params->getScreenYSize());
        m_iWindow = glutCreateWindow("jotak");
    }
    resizeWindow();

    glShadeModel(GL_SMOOTH);
    glDisable(GL_BLEND);
    glAlphaFunc(GL_GREATER, 0.0001f);
    glEnable(GL_ALPHA_TEST);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.05f, 0.1f, 0.0f);
    glClearDepth(1.0f);
    glClearStencil(0);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        _debug->notifyErrorMessage(string("Error in glewInit: ") + (char*) glewGetErrorString(err) + ".\n");
    }
    if (!glewIsSupported("GL_ARB_shading_language_100")) {
    	_debug->notifyErrorMessage("Warning: extension GL_ARB_shading_language_100 not supported.");
    }
    if (!glewIsSupported("GL_ARB_shader_objects")) {
    	_debug->notifyErrorMessage("Warning: extension GL_ARB_shader_objects not supported.");
    }
    if (!glewIsSupported("GL_ARB_vertex_shader")) {
    	_debug->notifyErrorMessage("Warning: extension GL_ARB_vertex_shader not supported.");
    }
    if (!glewIsSupported("GL_ARB_fragment_shader")) {
    	_debug->notifyErrorMessage("Warning: extension GL_ARB_fragment_shader not supported.");
    }

    for (list<Geometry*>::iterator it = m_pRegisteredGeometries.begin(); it != m_pRegisteredGeometries.end(); ++it) {
        (*it)->reload();
    }

    _tex->reloadAllTextures();
}

// ------------------------------------------------------------------
// Name : canResize
// ------------------------------------------------------------------
bool DisplayEngine::canResize()
{
	if (m_bIgnoreNextResize) {
		m_bIgnoreNextResize = false;
		return false;
	} else {
		return true;
	}
}

// ------------------------------------------------------------------
// Name : resizeWindow
// ------------------------------------------------------------------
void DisplayEngine::resizeWindow()
{
    //if (m_bLookAtMode)
    //{
    //  m_dScreenRatio = 16.0f / 9.0f;
    //  double hMargin = 0;
    //  double vMargin = 0;
    //  if (m_pClientParams->screenXSize > m_dScreenRatio * (double) m_pClientParams->screenYSize)
    //    vMargin = ((double) m_pClientParams->screenXSize - m_dScreenRatio * (double) m_pClientParams->screenYSize) / 2;
    //  else if (m_pClientParams->screenYSize > (double) m_pClientParams->screenXSize / m_dScreenRatio)
    //    hMargin = ((double) m_pClientParams->screenYSize - (double) m_pClientParams->screenXSize / m_dScreenRatio) / 2;
    //	glViewport(vMargin, hMargin, m_pClientParams->screenXSize - vMargin, m_pClientParams->screenYSize - hMargin);
    //}
    //else
    //{
    glViewport(0, 0, _params->getScreenXSize(), _params->getScreenYSize());
    m_dScreenRatio = BASE_WIDTH / BASE_HEIGHT;
//    m_dScreenRatio = (double) m_pClientParams->screenXSize / (double) m_pClientParams->screenYSize;
    //}
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-m_dScreenRatio, m_dScreenRatio, 1.0f, -1.0f, NEARPLANE, FARPLANE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    moveCameraTo(m_f3CamPos);
}

// ------------------------------------------------------------------
// Name : beginDisplay
// ------------------------------------------------------------------
void DisplayEngine::beginDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_iStencilDepth = 0;
    enableBlending();
}

// ------------------------------------------------------------------
// Name : endDisplay
// ------------------------------------------------------------------
void DisplayEngine::endDisplay()
{
    glutSwapBuffers();
}

// ------------------------------------------------------------------
// Name : begin2D
// ------------------------------------------------------------------
void DisplayEngine::begin2D()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, (GLdouble)_params->getScreenXSize(), (GLdouble)_params->getScreenYSize(), 0.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    m_ModeState = DMS_2D;
}

// ------------------------------------------------------------------
// Name : end2D
// ------------------------------------------------------------------
void DisplayEngine::end2D()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    m_ModeState = DMS_Undefined;
}

// ------------------------------------------------------------------
// Name : begin3D
// ------------------------------------------------------------------
void DisplayEngine::begin3D()
{
    m_ModeState = DMS_3D;
}

// ------------------------------------------------------------------
// Name : end3D
// ------------------------------------------------------------------
void DisplayEngine::end3D()
{
    m_ModeState = DMS_Undefined;
}

// ------------------------------------------------------------------
// Name : moveCameraBy
// ------------------------------------------------------------------
void DisplayEngine::moveCameraBy(Coords3D d3Delta)
{
    moveCameraTo(m_f3CamPos + d3Delta);
}

// ------------------------------------------------------------------
// Name : moveCameraTo
// ------------------------------------------------------------------
void DisplayEngine::moveCameraTo(Coords3D d3Pos)
{
    m_f3CamPos = d3Pos;
    glLoadIdentity();
    gluLookAt(m_f3CamPos.x, m_f3CamPos.y, -m_f3CamPos.z, m_f3CamPos.x - 0.5f, m_f3CamPos.y - 2.5f, -m_f3CamPos.z-BOARDPLANE, 0, 1, 0);
}

#define X2X   (2.0f * m_dScreenRatio)
#define X2Y   (2.0f)
#define M1X   (m_dScreenRatio)
#define M1Y   (1.0f)

// ------------------------------------------------------------------
// Name : getScreenCoords
// ------------------------------------------------------------------
CoordsScreen DisplayEngine::getScreenCoords(Coords3D d3Coords, DisplayModeState modeState)
{
    CoordsScreen screenCoords; // TODO
    return screenCoords;
}

// ------------------------------------------------------------------
// Name : get3DCoords
// ------------------------------------------------------------------
Coords3D DisplayEngine::get3DCoords(CoordsScreen screenCoords, DisplayModeState modeState)
{
    switch (modeState)
    {
    case DMS_2D:
        return Coords3D((double)screenCoords.x, (double)screenCoords.y, screenCoords.z);
    case DMS_3DCamIndependant:
    {
        Coords3D d3Coords(((double)screenCoords.x * X2X / (double)_params->getScreenXSize()) - M1X, ((double)screenCoords.y * X2Y / (double)_params->getScreenYSize()) - M1Y, screenCoords.z);
//      Coords3D d3Coords(((float)screenCoords.x * 2.0f / (float)m_pClientParams->screenXSize) - 1.0f, 1.0f - ((float)screenCoords.y * 2.0f / (float)m_pClientParams->screenYSize), screenCoords.z);
        return d3Coords;
    }
    case DMS_3D:
    default:
    {
        double fX = ((double)screenCoords.x * X2X / (double)_params->getScreenXSize()) - M1X;
        double fY = ((double)screenCoords.y * X2Y / (double)_params->getScreenYSize()) - M1Y;
//      float fX = ((float)screenCoords.x * 2.0f / (float)m_pClientParams->screenXSize) - 1.0f;
//      float fY = 1.0f - ((float)screenCoords.y * 2.0f / (float)m_pClientParams->screenYSize);
        Coords3D d3Coords(m_f3CamPos.x + fX * (screenCoords.z - m_f3CamPos.z) / NEARPLANE, m_f3CamPos.y + fY * (screenCoords.z - m_f3CamPos.z) / NEARPLANE, 0.0f);
        return d3Coords;
    }
    }
}

// ------------------------------------------------------------------
// Name : get3DDistance
// ------------------------------------------------------------------
Coords3D DisplayEngine::get3DDistance(CoordsScreen screenDist, DisplayModeState modeState)
{
    switch (modeState)
    {
    case DMS_2D:
        return Coords3D((double)screenDist.x, (double)screenDist.y, screenDist.z);
    case DMS_3D:
    default:
    {
        double fX = -(double)screenDist.x * X2X / (double)_params->getScreenXSize();
        double fY = -(double)screenDist.y * X2Y / (double)_params->getScreenYSize();
//      float fX = -(float)screenDist.x * 2.0f / (float)m_pClientParams->screenXSize;
//      float fY = (float)screenDist.y * 2.0f / (float)m_pClientParams->screenYSize;
        Coords3D d3Coords(fX * (screenDist.z - m_f3CamPos.z) / NEARPLANE, fY * (screenDist.z - m_f3CamPos.z) / NEARPLANE, 0.0f);
        return d3Coords;
    }
    }
}

// ------------------------------------------------------------------
// Name : setStencilState
//  return previous state
// ------------------------------------------------------------------
int DisplayEngine::setStencilState(int iState)
{
    int previous = m_iStencilState;
    m_iStencilState = iState;
    switch (iState)
    {
    case 0: // no stencil
        glDisable(GL_STENCIL_TEST);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        break;
    case 1: // fill stencil
        glEnable(GL_STENCIL_TEST);
        // Increase stencil to a higher depth when it's filled for current depth
        glStencilFunc(GL_EQUAL, m_iStencilDepth, 0xffffffff);
        glStencilOp(GL_KEEP, GL_INCR, GL_INCR);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDisable(GL_DEPTH_TEST);
        m_iStencilDepth++;
        break;
    case 2: // write with stencil
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_EQUAL, m_iStencilDepth, 0xffffffff);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        break;
    case 3: // unfill stencil
        glEnable(GL_STENCIL_TEST);
        // Decrease stencil to lower depth when it's filled for current depth
        glStencilFunc(GL_EQUAL, m_iStencilDepth, 0xffffffff);
        glStencilOp(GL_KEEP, GL_DECR, GL_DECR);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDisable(GL_DEPTH_TEST);
        m_iStencilDepth--;
        break;
    }
    return previous;
}

// ------------------------------------------------------------------
// Name : enableBlending
// ------------------------------------------------------------------
void DisplayEngine::enableBlending()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDepthMask(false);
}

// ------------------------------------------------------------------
// Name : disableBlending
// ------------------------------------------------------------------
void DisplayEngine::disableBlending()
{
    glDepthMask(true);
    glDisable(GL_BLEND);
}

// ------------------------------------------------------------------
// Name : setMaskBlending
// ------------------------------------------------------------------
void DisplayEngine::setMaskBlending(bool bGreyDarken)
{
//  glBlendEquation(GL_MIN);
//  glBlendFunc(GL_DST_COLOR, GL_ZERO);
    if (bGreyDarken) {
        glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
    }
}

// ------------------------------------------------------------------
// Name : startMaskBlending
// ------------------------------------------------------------------
void DisplayEngine::startMaskBlending()
{
//  glBlendEquation(GL_FUNC_ADD);
//  glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
//  glBlendFunc(GL_ONE, GL_ONE);
    glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
}

// ------------------------------------------------------------------
// Name : stopMaskBlending
// ------------------------------------------------------------------
void DisplayEngine::stopMaskBlending()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// ------------------------------------------------------------------
// Name : registerGeometry
// ------------------------------------------------------------------
void DisplayEngine::registerGeometry(Geometry * pGeometry)
{
    m_pRegisteredGeometries.push_back(pGeometry);
}

// ------------------------------------------------------------------
// Name : unregisterGeometry
// ------------------------------------------------------------------
void DisplayEngine::unregisterGeometry(Geometry * pGeometry)
{
	m_pRegisteredGeometries.remove(pGeometry);
}

// ------------------------------------------------------------------
// Name : saveWinPos
// ------------------------------------------------------------------
void DisplayEngine::saveWinPos()
{
    if (m_iWindow >= 0)  // windowed
    {
        _params->setWinXPos(glutGet(GLUT_WINDOW_X));
        _params->setWinYPos(glutGet(GLUT_WINDOW_Y));
    }
}

// ------------------------------------------------------------------
// Name : setAdditiveMode
// ------------------------------------------------------------------
bool DisplayEngine::setAdditiveMode(bool bAdd)
{
    bool bPrev = m_bAdditive;
    if (!bPrev && bAdd)
    {
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
        m_bAdditive = true;
    }
    else if (bPrev && !bAdd)
    {
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        m_bAdditive = false;
    }
    return bPrev;
}

// ------------------------------------------------------------------
// Name : loadShader
// ------------------------------------------------------------------
bool DisplayEngine::loadShader(GLuint * uShader, GLenum type, string sShader)
{
    *uShader = glCreateShader(type);
    if (*uShader == 0)
    {
        _debug->notifyErrorMessage("Error in loadShader: can't create shader " + sShader);
        return false;
    }

    // Open source file and read it
    string sFilePath = SHADERS_PATH + sShader;
    ifstream file(sFilePath.c_str());

    if (!file.is_open()) {
        glDeleteShader(*uShader);
        *uShader = 0;
        _debug->notifyErrorMessage("Error in loadShader: can't read source file " + sShader);
        return false;
    }

    string sContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Compile shader
    GLint status = GL_TRUE;
    glShaderSource(*uShader, 1, (const GLchar**) (sContent.c_str()), NULL);
    glCompileShader(*uShader);
    glGetShaderiv(*uShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char sLog[1024] = "";
        GLint size = 1024;  // wtf?
        glGetShaderInfoLog(*uShader, size, &size, sLog);
        _debug->notifyErrorMessage("Error in loadShader: can't compile " + sShader + ".\n" + sLog);
        glDeleteShader(*uShader);
        *uShader = 0;
        return false;
    }
    return true;
}

// ------------------------------------------------------------------
// Name : linkShaders
// ------------------------------------------------------------------
bool DisplayEngine::linkShaders(GLuint * uProgram, GLuint uVxShader, GLuint uPxShader)
{
    if (uVxShader == 0 && uPxShader == 0)
    {
    	_debug->notifyErrorMessage("Error in linkShaders: invalid shaders.");
        return false;
    }
    *uProgram = glCreateProgram();
    if (uVxShader != 0) {
        glAttachShader(*uProgram, uVxShader);
    }
    if (uPxShader != 0) {
        glAttachShader(*uProgram, uPxShader);
    }

    GLint status = GL_TRUE;
    glLinkProgram(*uProgram);
    glGetProgramiv(*uProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char sLog[1024] = "";
        GLint size = 1024;  // wtf?
        glGetProgramInfoLog(*uProgram, size, &size, sLog);
        _debug->notifyErrorMessage(string("Error in linkShaders: can't link program.\n") + sLog);
        glDeleteProgram(*uProgram);
        *uProgram = 0;
        return false;
    }
    return true;
}
