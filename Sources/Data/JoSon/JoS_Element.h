#ifndef _JOS_ELEMENT_H
#define _JOS_ELEMENT_H

#include <stdlib.h>
#include <cstring>
#include <iostream>

#define JOSON_TYPE_LEAF		1
#define JOSON_TYPE_LIST		2
#define JOSON_TYPE_MAP		3

class JoS_Element
{
public:
    // Constructor / destructor
	JoS_Element() {};
    virtual ~JoS_Element() {};

    virtual int getType() = 0;
    virtual std::string toString() = 0;
    virtual int toInt() = 0;
    virtual double toDouble() = 0;
    virtual JoS_Element * get() = 0;
    virtual JoS_Element * get(int) = 0;
    virtual JoS_Element * get(std::string) = 0;
};

#endif
