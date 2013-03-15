#ifndef _JOS_LIST_H
#define _JOS_LIST_H

#include <vector>
#include "JoS_Null.h"

class JoS_List : public JoS_Element
{
public:
    // Constructor / destructor
	JoS_List() {};
    ~JoS_List() { while (!m_list.empty()) { delete m_list.back(), m_list.pop_back(); } };

    void add(JoS_Element * item) { m_list.push_back(item); };
    int size() const { return m_list.size(); };
    JoS_Element& operator[](int idx) const { return *(m_list[idx]); };
    JoS_Element& operator[](std::string key) const { return JoS_Null::JoSNull; };
    std::string toString() const { return JoS_Null::JoSNull.toString(); };
    int toInt() const { return JoS_Null::JoSNull.toInt(); };
    double toDouble() const { return JoS_Null::JoSNull.toDouble(); };
    bool isMap() const { return false; };
    bool isList() const { return true; };
    bool isLeaf() const { return false; };
    bool isNull() const { return false; };

private:
    std::vector<JoS_Element*> m_list;
};

#endif
