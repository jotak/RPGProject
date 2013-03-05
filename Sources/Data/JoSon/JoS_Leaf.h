#ifndef _JOS_LEAF_H
#define _JOS_LEAF_H

#include "JoS_Null.h"

class JoS_Leaf : public JoS_Element
{
public:
    // Constructor / destructor
	JoS_Leaf() {};
    ~JoS_Leaf() {};

    void set(std::string leaf) { this->leaf = leaf; };
    const JoS_Element& operator[](int idx) const { return JoS_Null::JoSNull; };
    const JoS_Element& operator[](std::string key) const { return JoS_Null::JoSNull; };
    std::string toString() const { return leaf; };
    int toInt() const { return atoi(leaf.c_str()); };
    double toDouble() const { return atof(leaf.c_str()); };
    bool isMap() const { return false; };
    bool isList() const { return false; };
    bool isLeaf() const { return true; };
    bool isNull() const { return false; };

private:
    std::string leaf;
};

#endif
