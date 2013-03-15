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

    virtual std::string toString() const = 0;
    virtual int toInt() const = 0;
    virtual double toDouble() const = 0;
    virtual JoS_Element& operator[](int) const = 0;
    virtual JoS_Element& operator[](std::string) const = 0;
    virtual bool isMap() const = 0;
    virtual bool isList() const = 0;
    virtual bool isLeaf() const = 0;
    virtual bool isNull() const = 0;
    virtual int size() const = 0;
};

#endif
