#ifndef _JOS_NULL_H
#define _JOS_NULL_H

#include "JoS_Element.h"

class JoS_Null : public JoS_Element
{
public:
    // Constructor / destructor
	JoS_Null() {};
    ~JoS_Null() {};

    JoS_Element * get() { return this; };
    JoS_Element * get(int idx) { return this; };
    JoS_Element * get(std::string key) { return this; };
    std::string toString() { return ""; };
    int toInt() { return 0; };
    double toDouble() { return 0; };
    bool isMap() { return false; };
    bool isList() { return false; };
    bool isLeaf() { return false; };
    bool isNull() { return true; };

    static JoS_Null JoSNull;
};

#endif
