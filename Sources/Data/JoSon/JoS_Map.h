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
    JoS_Element * get() { return &(JoS_Null::JoSNull); };
    JoS_Element * get(int idx) { return &(JoS_Null::JoSNull); };
    JoS_Element * get(std::string key) {
    	jos_map::iterator it = m_map.find(key);
    	if (it != m_map.end()) {
    		return it->second;
    	} else {
    		return &(JoS_Null::JoSNull);
    	}
    };
    std::string toString() { return JoS_Null::JoSNull.toString(); };
    int toInt() { return JoS_Null::JoSNull.toInt(); };
    double toDouble() { return JoS_Null::JoSNull.toDouble(); };
    bool isMap() { return true; };
    bool isList() { return false; };
    bool isLeaf() { return false; };
    bool isNull() { return false; };

private:
    jos_map m_map;
};

#endif
