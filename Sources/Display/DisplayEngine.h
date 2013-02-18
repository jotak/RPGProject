#ifndef _DISPLAY_ENGINE_H
#define _DISPLAY_ENGINE_H

#include "../Geometries/Geometry.h"

#define NEARPLANE                   0.1f
#define FARPLANE                    1000.0f
#define GUIPLANE                    1.0f
#define BOARDPLANE                  100.0f
#define BUFFER_OFFSET(i)            ((char*)NULL + (i))

enum DisplayModeState
{
    DMS_Undefined = 0,
    DMS_2D,
    DMS_3D,
    DMS_3DCamIndependant,
};

class DisplayEngine
{
public:
    // Singleton / destructor
    ~DisplayEngine();
    static DisplayEngine * getInstance()
    {
        if (m_pInstance == NULL) m_pInstance = new DisplayEngine();
        return m_pInstance;
    };

    void init();
    void initGlutWindow();
    void setMapData(int iWidth, int iHeight)
    {
        m_iMapWidth = iWidth;
        m_iMapHeight = iHeight;
    };

    // Other functions
    void beginDisplay();
    void endDisplay();
    void begin2D();
    void end2D();
    void begin3D();
    void end3D();
    bool isReady() { return m_bReady; };
    void setReady() { m_bReady = true; };
    void resizeWindow();
    CoordsMap getMapCoords(CoordsScreen screenCoords);
    CoordsMap getMapCoords(Coords3D d3Coords);
    CoordsScreen getScreenCoords(CoordsMap mapCoords);
    CoordsScreen getScreenCoords(Coords3D d3Coords, DisplayModeState modeState);
    Coords3D get3DCoords(CoordsMap mapCoords, double fZPlane = BOARDPLANE);
    Coords3D get3DCoords(CoordsScreen screenCoords, DisplayModeState modeState);
    Coords3D get3DDistance(CoordsScreen screenDist, DisplayModeState modeState);
    Coords3D getCamera() { return m_f3CamPos; };
    void moveCameraBy(Coords3D d3Delta);
    void moveCameraTo(Coords3D d3Delta);
    void setModeState(DisplayModeState modeState) { m_ModeState = modeState; };
    bool isZoomToMapPosNeeded(CoordsMap mapPos);
    int setStencilState(int iState);
    void enableBlending();
    void disableBlending();
    void setMaskBlending(bool bGreyDarken);
    void startMaskBlending();
    void stopMaskBlending();
    void registerGeometry(Geometry * pGeometry);
    void unregisterGeometry(Geometry * pGeometry);
    void saveWinPos();
    bool setAdditiveMode(bool bAdd);
    void setLookAtMode(bool bLookAt);
    bool canResize();

    // Shaders
    bool loadShader(GLuint * uShader, GLenum type, string sShader);
    bool linkShaders(GLuint * uProgram, GLuint uVxShader, GLuint uPxShader);

private:
    DisplayEngine();
    static DisplayEngine * m_pInstance;

    Coords3D m_f3CamPos;
    DisplayModeState m_ModeState;
    bool m_bReady;
    int m_iStencilState;  // 0 = no stencil, 1 = fill stencil, 2 = write with stencil
    int m_iStencilDepth;
    int m_iWindow;
    list<Geometry*> m_pRegisteredGeometries;
    double m_dScreenRatio;
    int m_iMapWidth;
    int m_iMapHeight;
    bool m_bAdditive;
    bool m_bLookAtMode;
    bool m_bIgnoreNextResize;
};

// Helper alias
#define _display DisplayEngine::getInstance()

#endif
