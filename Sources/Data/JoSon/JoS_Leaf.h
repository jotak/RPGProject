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
    JoS_Element * get() { return this; };
    JoS_Element * get(int idx) { return &(JoS_Null::JoSNull); };
    JoS_Element * get(std::string key) { return &(JoS_Null::JoSNull); };
    std::string toString() { return leaf; };
    int toInt() { return atoi(leaf.c_str()); };
    double toDouble() { return atof(leaf.c_str()); };
    bool isMap() { return false; };
    bool isList() { return false; };
    bool isLeaf() { return true; };
    bool isNull() { return false; };

private:
    std::string leaf;
};

#endif
