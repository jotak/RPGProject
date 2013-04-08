// -----------------------------------------------------------------
// GAME OBJECT
// -----------------------------------------------------------------
#include "GameObject.h"
#include "../Display/DisplayEngine.h"
#include "../Managers/WorldManager.h"

// -----------------------------------------------------------------
// Name : GameObject
// -----------------------------------------------------------------
GameObject::GameObject()
{
}

// -----------------------------------------------------------------
// Name : ~GameObject
// -----------------------------------------------------------------
GameObject::~GameObject()
{
	FREE(m_pGeometry);
}

// -----------------------------------------------------------------
// Name : operator<< (~toString)
// -----------------------------------------------------------------
ostream& operator<< (ostream& stream, const GameObject& obj) {
	stream << obj.toString();
	return stream;
}

// -----------------------------------------------------------------
// Name : toString
// -----------------------------------------------------------------
string GameObject::toString() const {
	std::ostringstream oss;
	oss << "x: " << m_pos.x << " | y: " << m_pos.y;
	return oss.str();
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void GameObject::update(double delta)
{
	if (m_pGeometry != NULL) {
		m_pGeometry->update(delta);
	}
}

// -----------------------------------------------------------------
// Name : display
// -----------------------------------------------------------------
void GameObject::display()
{
	if (m_pGeometry != NULL) {
		m_pGeometry->display(m_pos, Color::white);
	}
}

// -----------------------------------------------------------------
// Name : setPosition
// -----------------------------------------------------------------
void GameObject::setPosition(f3d newPos)
{
	if (newPos != m_pos) {
		m_pos = newPos;
		SpacePart * pSpacePartition = _world->getSpacePartition();
		if (pSpacePartition != NULL) {
			pSpacePartition->put(this);
		}
	}
}
