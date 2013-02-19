#ifndef _JOS_MAP_H
#define _JOS_MAP_H

#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <tr1/unordered_map>
#include "JoS_Element.h"

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
    JoS_Element * get() { return this; };
    JoS_Element * get(int idx) { return this; };
    JoS_Element * get(std::string key) { return m_map[key]; };
    std::string toString() { return ""; };
    int toInt() { return 0; };
    double toDouble() { return 0; };

private:
    jos_map m_map;
};

#endif
