#ifndef _JOS_LEAF_H
#define _JOS_LEAF_H

#include "JoS_Element.h"

class JoS_Leaf : public JoS_Element
{
public:
    // Constructor / destructor
	JoS_Leaf() {};
    ~JoS_Leaf() {};

    int getType() { return JOSON_TYPE_LEAF; };
    void set(std::string leaf) { this->leaf = leaf; };
    JoS_Element * get() { return this; };
    JoS_Element * get(int idx) { return this; };
    JoS_Element * get(std::string key) { return this; };
    std::string toString() { return leaf; };
    int toInt() { return atoi(leaf.c_str()); };
    double toDouble() { return atof(leaf.c_str()); };

private:
    std::string leaf;
};

#endif
