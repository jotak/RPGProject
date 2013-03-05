// -----------------------------------------------------------------
// CHARACTER
// -----------------------------------------------------------------
#include "Character.h"
#include "../Physics/MovesHelper.h"

// -----------------------------------------------------------------
// Name : Character
// -----------------------------------------------------------------
Character::Character(const JoS_Element &json)
{
	setSpeed(getJsonDouble(json, "speed", 5.0f));
	const JoS_Element& jsTraits = json["traits"];
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
int Character::getJsonInt(const JoS_Element &json, string name, int defaultVal)
{
	const JoS_Element& elt = json[name];
	if (elt.isList() && elt[0].isLeaf() && elt[1].isLeaf()) {
		// Case list of 2 elements => random in min/max
		int min = elt[0].toInt();
		int max = elt[1].toInt();
		return min + rand() % (1+max-min);
	} else if (elt.isLeaf()) {
		return elt.toInt();
	} else {
		return defaultVal;
	}
}

// -----------------------------------------------------------------
// Name : getJsonDouble
// -----------------------------------------------------------------
double Character::getJsonDouble(const JoS_Element &json, string name, double defaultVal)
{
	const JoS_Element& elt = json[name];
	if (elt.isList() && elt[0].isLeaf() && elt[1].isLeaf()) {
		// Case list of 2 elements => random in min/max
		double min = elt[0].toDouble();
		double max = elt[1].toDouble();
		return min + FRAND100(max-min);
	} else if (elt.isLeaf()) {
		return elt.toDouble();
	} else {
		return defaultVal;
	}
}

// -----------------------------------------------------------------
// Name : getJsonString
// -----------------------------------------------------------------
string Character::getJsonString(const JoS_Element &json, string name, string defaultVal)
{
	const JoS_Element& elt = json[name];
	if (elt.isList()) {
		// Enumeration of strings => take random one
		int idx = rand() % ((JoS_List&)elt).size();
		return elt[idx].toString();
	} else if (elt.isLeaf()) {
		return elt.toString();
	} else {
		return defaultVal;
	}
}
