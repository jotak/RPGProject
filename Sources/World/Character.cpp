// -----------------------------------------------------------------
// CHARACTER
// -----------------------------------------------------------------
#include "Character.h"
#include "../Physics/MovesHelper.h"
#include "../Data/JoSon/JoSon.h"

// -----------------------------------------------------------------
// Name : Character
// -----------------------------------------------------------------
Character::Character(JoS_Element * json)
{
	setSpeed(getJsonDouble(json, "speed", 5.0f));
	JoS_Element * jsTraits = json->get("traits");
	m_mapTraits["friendly"] = getJsonInt(jsTraits, "friendly", 0);
	m_mapTraits["funny"] = getJsonInt(jsTraits, "funny", 0);
}

// -----------------------------------------------------------------
// Name : ~Character
// -----------------------------------------------------------------
Character::~Character()
{
}

// -----------------------------------------------------------------
// Name : operator<< (~toString)
// -----------------------------------------------------------------
ostream& operator<< (ostream& stream, const Character& character) {
	f3d pos = character.getPosition();
	stream << "x: " << pos.x << " / y: " << pos.y << " / speed: " << character.speed;
	for (pair<string, long> entry : character.m_mapTraits) {
		stream << " / " << entry.first << ": " << entry.second;
	}
	return stream;
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void Character::update(double delta)
{
	MovingObject::update(delta);
}

// -----------------------------------------------------------------
// Name : setMoveTarget
// -----------------------------------------------------------------
void Character::setMoveTarget(Coords3D pos)
{
	setMovement(MovesHelper::newConstantMove(pos - getPosition(), speed));
}

// -----------------------------------------------------------------
// Name : getJsonInt
// -----------------------------------------------------------------
int Character::getJsonInt(JoS_Element * json, string name, int defaultVal)
{
	JoS_Element * elt = json->get(name);
	if (elt->isList() && elt->get(0)->isLeaf() && elt->get(1)->isLeaf()) {
		// Case list of 2 elements => random in min/max
		int min = elt->get(0)->get()->toInt();
		int max = elt->get(1)->get()->toInt();
		return min + rand() % (1+max-min);
	} else if (!elt->isLeaf()) {
		return defaultVal;
	} else {
		return elt->get()->toInt();
	}
}

// -----------------------------------------------------------------
// Name : getJsonDouble
// -----------------------------------------------------------------
double Character::getJsonDouble(JoS_Element * json, string name, double defaultVal)
{
	JoS_Element * elt = json->get(name);
	if (elt->isList() && elt->get(0)->isLeaf() && elt->get(1)->isLeaf()) {
		// Case list of 2 elements => random in min/max
		double min = elt->get(0)->get()->toDouble();
		double max = elt->get(1)->get()->toDouble();
		return min + FRAND100(max-min);
	} else if (!elt->isLeaf()) {
		return defaultVal;
	} else {
		return elt->get()->toDouble();
	}
}

// -----------------------------------------------------------------
// Name : getJsonString
// -----------------------------------------------------------------
string Character::getJsonString(JoS_Element * json, string name, string defaultVal)
{
	JoS_Element * elt = json->get(name);
	if (elt->isList()) {
		// Enumeration of strings => take random one
		int idx = rand() % ((JoS_List*)elt)->size();
		return elt->get(idx)->toString();
	} else if (!elt->isLeaf()) {
		return defaultVal;
	} else {
		return elt->get()->toString();
	}
}
