#ifndef _JOS_LIST_H
#define _JOS_LIST_H

#include <vector>
#include "JoS_Null.h"

class JoS_List : public JoS_Element
{
public:
    // Constructor / destructor
	JoS_List() {};
    virtual ~JoS_List() { while (!m_list.empty()) { delete m_list.back(), m_list.pop_back(); } };

    virtual void add(JoS_Element * item) { m_list.push_back(item); };
    virtual int size() const { return m_list.size(); };
    virtual JoS_Element& operator[](int idx) const { if (idx >= 0 && idx < (int) m_list.size()) return *(m_list[idx]); return JoS_Null::JoSNull; };
    virtual JoS_Element& operator[](std::string key) const { return JoS_Null::JoSNull; };
    virtual std::string toString() const { return JoS_Null::JoSNull.toString(); };
    virtual int toInt() const { return JoS_Null::JoSNull.toInt(); };
    virtual double toDouble() const { return JoS_Null::JoSNull.toDouble(); };
    virtual bool isMap() const { return false; };
    virtual bool isList() const { return true; };
    virtual bool isLeaf() const { return false; };
    virtual bool isNull() const { return false; };

private:
    std::vector<JoS_Element*> m_list;
};

#endif
