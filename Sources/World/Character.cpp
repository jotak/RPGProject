// -----------------------------------------------------------------
// CHARACTER
// -----------------------------------------------------------------
#include "Character.h"
#include "../Physics/MovesHelper.h"
#include "../Managers/DebugManager.h"
#include "../Data/JSonUtil.h"

JoSon * Character::TraitsRelations = NULL;
jos_map Character::CommonDialogs;

// -----------------------------------------------------------------
// Name : Character
// -----------------------------------------------------------------
Character::Character(const JoS_Element &json)
{
	name = JSonUtil::getString(json["name"], "Dude");
	setSpeed(JSonUtil::getDouble(json["speed"], 5.0f));
	const JoS_Element& jsTraits = json["traits"];

	int nbTraits = (*TraitsRelations)["_list_"].size();
	for (int i = 0; i < nbTraits; i++) {
		string trait = (*TraitsRelations)["_list_"][i].toString();
		mapTraits[trait] = JSonUtil::getCappedInt(jsTraits[trait], 0, TRAIT_MAX_VALUE);
	}

    bCanMove = true;
    bHasMoveTarget = false;
}

// -----------------------------------------------------------------
// Name : ~Character
// -----------------------------------------------------------------
Character::~Character()
{
}

// -----------------------------------------------------------------
// Name : toString
// -----------------------------------------------------------------
string Character::toString() const {
	std::ostringstream oss;
	oss << GameObject::toString();
	oss << " | speed: " << speed;
	for (pair<string, long> entry : mapTraits) {
		if (entry.second != 0) {
			oss << " | " << entry.first << ": " << entry.second;
		}
	}
	return oss.str();
}

// -----------------------------------------------------------------
// Name : update
// -----------------------------------------------------------------
void Character::update(double delta)
{
	MovingObject::update(delta);
	if (bHasMoveTarget && bCanMove) {
		doMove(delta * get3DSpeed());
	}
}

// -----------------------------------------------------------------
// Name : doMove
// -----------------------------------------------------------------
void Character::doMove(double step)
{
	// TODO: pathfinder
    f3d pos = getPosition();
    f3d globalMove = moveTarget - pos;
    double distanceToGoal = globalMove.getSize();
    if (distanceToGoal <= step) {
    	// Character has arrived
    	setPosition(moveTarget);
    	bHasMoveTarget = false;
    } else {
    	setPosition(pos + globalMove.getUnitVector(distanceToGoal) * step);
    }
}

// -----------------------------------------------------------------
// Name : get3DSpeed
//	"speed" stands for the speed characteristic; it must be relativised to board metrics
// -----------------------------------------------------------------
double Character::get3DSpeed()
{
	return 2.0f + speed / 2.0f;
}

// -----------------------------------------------------------------
// Name : goToGround
// -----------------------------------------------------------------
void Character::goToGround(f3d pos2D)
{
	bHasMoveTarget = true;
	moveTarget = pos2D;
	moveTarget.z = BOARDPLANE;
}

// -----------------------------------------------------------------
// Name : goToGround
// -----------------------------------------------------------------
void Character::goToGround(double x, double y)
{
	bHasMoveTarget = true;
	moveTarget = f3d(x, y, BOARDPLANE);
}

// -----------------------------------------------------------------
// Name : say
// -----------------------------------------------------------------
void Character::say(string sentence)
{
	cout << name << ": " << sentence << endl;
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
    TraitsRelations = JoSon::fromFile(jsonDesc, &err);
    if (TraitsRelations == NULL) {
    	_debug->error(err);
    }
}

// -----------------------------------------------------------------
// Name : getCommonDialogs
//	This method looks for a dialog json object. First try to check if it's already loaded ; else try to load it from file
//	static
// -----------------------------------------------------------------
JoS_Element& Character::getCommonDialogs(string name)
{
	jos_map::iterator it = CommonDialogs.find(name);
	if (it != CommonDialogs.end()) {
		return *(it->second);
	} else {
	    // Build file name
	    string jsonDesc = string(AI_PATH) + name;
	    string err;
	    JoSon * json = JoSon::fromFile(jsonDesc, &err);
	    if (json == NULL) {
	    	_debug->error(err);
			return JoS_Null::JoSNull;
	    } else {
	    	CommonDialogs[name] = json;
	    	return *json;
	    }
	}
}

// -----------------------------------------------------------------
// Name : releaseData
//	static
// -----------------------------------------------------------------
void Character::releaseData()
{
	FREE(TraitsRelations);
	for (pair<string, JoS_Element*> entry : CommonDialogs) {
		delete entry.second;
	}
	CommonDialogs.clear();
}

// -----------------------------------------------------------------
// Name : getTraitsRelation
// Relation is not comutable: getTraitsRelation(A, B) != getTraitsRelation(B, A)
//	static
// -----------------------------------------------------------------
float Character::getTraitsRelation(string from, string towards)
{
	if (TraitsRelations != NULL && !(*TraitsRelations)[from][towards].isNull()) {
		float value = (float) (*TraitsRelations)[from][towards].toDouble();
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
