#ifndef _JOS_LIST_H
#define _JOS_LIST_H

#include <vector>
#include "JoS_Element.h"

class JoS_List : public JoS_Element
{
public:
    // Constructor / destructor
	JoS_List() {};
    ~JoS_List() { while (!m_list.empty()) { delete m_list.back(), m_list.pop_back(); } };

    void add(JoS_Element * item) { m_list.push_back(item); };
    int size() { return m_list.size(); };
    JoS_Element * get() { return this; };
    JoS_Element * get(int idx) { return m_list[idx]; };
    JoS_Element * get(std::string key) { return this; };
    std::string toString() { return ""; };
    int toInt() { return 0; };
    double toDouble() { return 0; };

private:
    std::vector<JoS_Element*> m_list;
};

#endif
