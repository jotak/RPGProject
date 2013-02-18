// -----------------------------------------------------------------
// JoSon
// -----------------------------------------------------------------
#include "JoSon.h"
#include <sstream>
#include <fstream>

// -----------------------------------------------------------------
// Name : JoSon
// -----------------------------------------------------------------
JoSon::JoSon()
{
	m_pRoot = NULL;
	m_sError = "";
}

// -----------------------------------------------------------------
// Name : ~JoSon
// -----------------------------------------------------------------
JoSon::~JoSon()
{
	if (m_pRoot != NULL) {
		delete m_pRoot;
	}
}

// -----------------------------------------------------------------
// Name : getNextChar
// -----------------------------------------------------------------
char JoSon::getNextChar(std::stringstream * stream)
{
	while (stream->good()) {
		char c = stream->get();
		if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
			return c;
		}
	}
	return 0;
}

// -----------------------------------------------------------------
// Name : readString
// -----------------------------------------------------------------
std::string JoSon::readString(std::stringstream * stream)
{
	std::stringstream str;

	char first = 0;
	char c = getNextChar(stream);
	if (c == '\"' || c == '\'') {
		first = c;
		while (stream->good()) {
			c = stream->get();
			if (c == first) {
				break;
			} else {
				str << c;
			}
		}
	} else {
		stream->unget();
		while (stream->good()) {
			c = stream->get();
			if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == ',' || c == ':' || c == ']' || c == '}') {
				// This is end of string condition
				stream->unget();
				break;
			} else {
				str << c;
			}
		}
	}

	return str.str();
}

// -----------------------------------------------------------------
// Name : expect
// -----------------------------------------------------------------
bool JoSon::expect(std::stringstream * stream, char expected)
{
	char c = getNextChar(stream);
	if (c != expected) {
		// Syntax error
		m_sError = std::string("Syntax error: '") + expected + "' expected.";
		return false;
	} else {
		return true;
	}
}

// -----------------------------------------------------------------
// Name : readMap
// -----------------------------------------------------------------
JoS_Map * JoSon::readMap(std::stringstream * stream)
{
	JoS_Map * map = new JoS_Map();

	std::string key = readString(stream);
	while (key != "") {

		if (!expect(stream, ':')) {
			delete map;
			return NULL;
		}

		JoS_Element * value = readAny(stream);
		if (value != NULL) {
			map->put(key, value);
		} else {
			delete map;
			return NULL;
		}

		if (!expect(stream, ',')) {
			stream->unget();
			break;
		}

		key = readString(stream);
	}

	if (!expect(stream, '}')) {
		delete map;
		return NULL;
	}

	return map;
}

// -----------------------------------------------------------------
// Name : readList
// -----------------------------------------------------------------
JoS_List * JoSon::readList(std::stringstream * stream)
{
	JoS_List * list = new JoS_List();

	while (stream->good()) {

		JoS_Element * value = readAny(stream);
		if (value != NULL) {
			list->add(value);
		} else {
			delete list;
			return NULL;
		}

		if (!expect(stream, ',')) {
			stream->unget();
			break;
		}

	}

	if (!expect(stream, ']')) {
		delete list;
		return NULL;
	}

	return list;
}

// -----------------------------------------------------------------
// Name : readLeaf
// -----------------------------------------------------------------
JoS_Leaf * JoSon::readLeaf(std::stringstream * stream)
{
	JoS_Leaf * leaf = new JoS_Leaf();
	leaf->set(readString(stream));
	return leaf;
}

// -----------------------------------------------------------------
// Name : readAny
// -----------------------------------------------------------------
JoS_Element * JoSon::readAny(std::stringstream * stream)
{
	char nextc = getNextChar(stream);
	switch (nextc) {
	case '{':
		return readMap(stream);
	case '[':
		return readList(stream);
	default:
		stream->unget();
		return readLeaf(stream);
	}
}

// -----------------------------------------------------------------
// Name : fromString
// -----------------------------------------------------------------
JoSon * JoSon::fromString(std::string strJoson, std::string * sError)
{
	JoSon * joSon = new JoSon();
	std::stringstream ss(strJoson);
	joSon->m_pRoot = joSon->readAny(&ss);
	if (joSon->m_pRoot == NULL) {
		*sError = std::string("JoSon error, fromString: ") + joSon->m_sError;
		delete joSon;
		return NULL;
	}
	return joSon;
}

// -----------------------------------------------------------------
// Name : fromFile
// -----------------------------------------------------------------
JoSon * JoSon::fromFile(std::string fileJoson, std::string * sError)
{
	std::ifstream file(fileJoson.c_str());
	if (file.is_open()) {
	    std::string contents;
	    file.seekg(0, std::ios::end);
	    unsigned int size = file.tellg();
	    contents.resize(size);
	    file.seekg(0, std::ios::beg);
	    file.read(&contents[0], contents.size());
	    file.close();

	    // Now parse string
		JoSon * joSon = fromString(contents, sError);
		if (joSon == NULL) {
			*sError = *sError + ", fromFile[" + fileJoson + "]";
			return NULL;
		} else {
			return joSon;
		}
	} else {
		*sError = std::string("JoSon error, fromFile[") + fileJoson + "]";
		return NULL;
	}
}
