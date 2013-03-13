#ifndef _JOS_NULL_H
#define _JOS_NULL_H

#include "JoS_Element.h"

class JoS_Null : public JoS_Element
{
public:
    // Constructor / destructor
	JoS_Null() {};
    ~JoS_Null() {};

    const JoS_Element& operator[](int idx) const { return JoSNull; };
    const JoS_Element& operator[](std::string key) const { return JoSNull; };
    std::string toString() const { return ""; };
    int toInt() const { return 0; };
    double toDouble() const { return 0; };
    bool isMap() const { return false; };
    bool isList() const { return false; };
    bool isLeaf() const { return false; };
    bool isNull() const { return true; };
    int size() const { return 0; };

    static JoS_Null JoSNull;
};

#endif
