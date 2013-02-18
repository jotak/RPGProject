#include "ModProgressiveRotate.h"

// -----------------------------------------------------------------
// Name : ModProgressiveRotate
//  Constructor
// -----------------------------------------------------------------
ModProgressiveRotate::ModProgressiveRotate(u16 uModId, float fSpeed, float fCenterX, float fCenterY)
    : GeometryModifier(uModId)
{
    m_fAngle = 0;
    m_fSpeed = fSpeed;
    m_fRotateCenterX = fCenterX;
    m_fRotateCenterY = fCenterY;
}

// -----------------------------------------------------------------
// Name : ~ModProgressiveRotate
//  Destructor
// -----------------------------------------------------------------
ModProgressiveRotate::~ModProgressiveRotate()
{
}

// -----------------------------------------------------------------
// Name : doTransforms
// -----------------------------------------------------------------
void ModProgressiveRotate::doTransforms(Color * pColor)
{
    glTranslatef(m_fRotateCenterX, m_fRotateCenterY, 0);
    glRotatef(m_fAngle, 0, 0, 1);
    glTranslatef(-m_fRotateCenterX, -m_fRotateCenterY, 0);
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void ModProgressiveRotate::update(double delta)
{
    m_fAngle += m_fSpeed * delta;
    while (m_fAngle >= 360) {
        m_fAngle -= 360;
    }
}

// -----------------------------------------------------------------
// Name : clone
// -----------------------------------------------------------------
GeometryModifier * ModProgressiveRotate::clone(u16 uMoveId)
{
    ModProgressiveRotate * pClone = new ModProgressiveRotate(uMoveId, m_fSpeed, m_fRotateCenterX, m_fRotateCenterY);
    return pClone;
}
