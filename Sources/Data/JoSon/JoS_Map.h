#ifndef _JOS_MAP_H
#define _JOS_MAP_H

#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <tr1/unordered_map>
#include "JoS_Null.h"

typedef std::tr1::unordered_map<std::string, JoS_Element*> jos_map;

class JoS_Map : public JoS_Element
{
public:
    // Constructor / destructor
	JoS_Map() {};
    ~JoS_Map() {
    	for (jos_map::iterator it = m_map.begin(); it != m_map.end(); ++it) {
    		delete it->second;
    	}
    	m_map.clear();
    };

    bool put(std::string key, JoS_Element * value) {
    	jos_map::iterator it = m_map.find(key);
    	if (it != m_map.end()) {
    		return false;
    	} else {
    		m_map[key] = value;
    		return true;
    	}
    };
    JoS_Element& operator[](int idx) const { return JoS_Null::JoSNull; };
    JoS_Element& operator[](std::string key) const {
    	jos_map& map = const_cast<JoS_Map*>(this)->m_map;
    	jos_map::iterator it = map.find(key);
    	if (it != map.end()) {
    		return *(it->second);
    	} else {
    		return JoS_Null::JoSNull;
    	}
    };
    std::string toString() const { return JoS_Null::JoSNull.toString(); };
    int toInt() const { return JoS_Null::JoSNull.toInt(); };
    double toDouble() const { return JoS_Null::JoSNull.toDouble(); };
    bool isMap() const { return true; };
    bool isList() const { return false; };
    bool isLeaf() const { return false; };
    bool isNull() const { return false; };
    int size() const { return m_map.size(); };

private:
    jos_map m_map;
};

#endif
