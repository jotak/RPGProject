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
    int size() { return m_list.size(); };
    JoS_Element * get() { return &(JoS_Null::JoSNull); };
    JoS_Element * get(int idx) { return m_list[idx]; };
    JoS_Element * get(std::string key) { return &(JoS_Null::JoSNull); };
    std::string toString() { return JoS_Null::JoSNull.toString(); };
    int toInt() { return JoS_Null::JoSNull.toInt(); };
    double toDouble() { return JoS_Null::JoSNull.toDouble(); };
    bool isMap() { return false; };
    bool isList() { return true; };
    bool isLeaf() { return false; };
    bool isNull() { return false; };

private:
    std::vector<JoS_Element*> m_list;
};

#endif
