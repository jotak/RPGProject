#ifndef _JOS_ELEMENT_H
#define _JOS_ELEMENT_H

#include <stdlib.h>
#include <cstring>
#include <iostream>

class JoS_Element
{
public:
    // Constructor / destructor
	JoS_Element() {};
    virtual ~JoS_Element() {};

    virtual std::string toString() = 0;
    virtual int toInt() = 0;
    virtual double toDouble() = 0;
    virtual JoS_Element * get() = 0;
    virtual JoS_Element * get(int) = 0;
    virtual JoS_Element * get(std::string) = 0;
};

#endif
