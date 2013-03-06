// -----------------------------------------------------------------
// CHARACTER
// -----------------------------------------------------------------
#include "Character.h"
#include "../Physics/MovesHelper.h"
#include "../Managers/DebugManager.h"

JoSon * Character::m_pTraitsRelations = NULL;

// -----------------------------------------------------------------
// Name : Character
// -----------------------------------------------------------------
Character::Character(const JoS_Element &json)
{
	setSpeed(getJsonDouble(json, "speed", 5.0f));
	const JoS_Element& jsTraits = json["traits"];

	int nbTraits = ((JoS_List&)((*m_pTraitsRelations)["_list_"])).size();
	for (int i = 0; i < nbTraits; i++) {
		string trait = (*m_pTraitsRelations)["_list_"][i].toString();
		m_mapTraits[trait] = getJsonInt(jsTraits, trait, 0, 0, TRAIT_MAX_VALUE);
	}
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
		if (entry.second != 0) {
			stream << " / " << entry.first << ": " << entry.second;
		}
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
int Character::getJsonInt(const JoS_Element &json, string name, int defaultVal, int capMin, int capMax)
{
	int val = defaultVal;
	const JoS_Element& elt = json[name];
	if (elt.isList() && elt[0].isLeaf() && elt[1].isLeaf()) {
		// Case list of 2 elements => random in min/max
		int min = elt[0].toInt();
		int max = elt[1].toInt();
		val = min + rand() % (1+max-min);
	} else if (elt.isLeaf()) {
		val = elt.toInt();
	}

	// Min/max capping
	if (val < capMin) {
		val = capMin;
		ostringstream os; os << name << " capped up to " << capMin;
		_debug->notifyErrorMessage(os.str());
	} else if (val > capMax) {
		val = capMax;
		ostringstream os; os << name << " capped down to " << capMax;
		_debug->notifyErrorMessage(os.str());
	}

	return val;
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

// -----------------------------------------------------------------
// Name : initData
//	static
// -----------------------------------------------------------------
void Character::initData()
{
    // Build file name
    string jsonDesc = string(AI_PATH) + "traitsRelations.json";
    string err;
    m_pTraitsRelations = JoSon::fromFile(jsonDesc, &err);
    if (m_pTraitsRelations == NULL) {
    	_debug->notifyErrorMessage(err);
    }
}

// -----------------------------------------------------------------
// Name : releaseData
//	static
// -----------------------------------------------------------------
void Character::releaseData()
{
	FREE(m_pTraitsRelations);
}

// -----------------------------------------------------------------
// Name : getTraitsRelation
// Relation is not comutable: getTraitsRelation(A, B) != getTraitsRelation(B, A)
//	static
// -----------------------------------------------------------------
float Character::getTraitsRelation(string from, string towards)
{
	if (m_pTraitsRelations != NULL && !(*m_pTraitsRelations)[from][towards].isNull()) {
		float value = (float) (*m_pTraitsRelations)[from][towards].toDouble();
		// Cap value in [-1,1]
		if (value > 1.0f) {
			value = 1.0f;
		} else if (value < -1.0f) {
			value = -1.0f;
		}
		return value;
	}
	// Value not found => neutral relation
	return 0.0f;
}
