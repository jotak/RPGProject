#ifndef _JOS_UNION_H
#define _JOS_UNION_H

#include "JoS_List.h"

class JoS_Union : public JoS_Element
{
public:
    // Constructor / destructor
	JoS_Union(JoS_Element& first) : m_first(first) { m_second = NULL; };
	~JoS_Union() { if (m_second != NULL) delete m_second; };

	JoS_Union * concat(JoS_Element& second) { m_second = new JoS_Union(second); return m_second; };
    int size() const { if (m_second != NULL) return m_first.size() + m_second->size(); return m_first.size(); };
    JoS_Element& operator[](int idx) const {
    	int size = m_first.size();
    	if (idx < size) {
    		return m_first[idx];
    	} else if (m_second != NULL) {
    		return (*m_second)[idx - size];
    	} else {
    		return JoS_Null::JoSNull;
    	}
    };
    JoS_Element& operator[](std::string key) const {
    	JoS_Element& elt = m_first[key];
    	if (elt.isNull() && m_second != NULL) {
    		return (*m_second)[key];
    	} else {
    		return elt;
    	}
    };
    std::string toString() const { if (m_second != NULL) return m_first.toString() + m_second->toString(); return m_first.toString(); };
    int toInt() const { if (m_second != NULL) return m_first.toInt() + m_second->toInt(); return m_first.toInt(); };
    double toDouble() const { if (m_second != NULL) return m_first.toDouble() + m_second->toDouble(); return m_first.toDouble(); };
    bool isMap() const { return false; };
    bool isList() const { return false; };
    bool isLeaf() const { return false; };
    bool isNull() const { return false; };

private:
    JoS_Element& m_first;
    JoS_Union * m_second;
};

#endif
