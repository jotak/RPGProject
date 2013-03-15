#ifndef _JOSON_H
#define _JOSON_H

#include "JoS_Leaf.h"
#include "JoS_List.h"
#include "JoS_Map.h"

class JoSon : public JoS_Element
{
public:
    // Destructor
    ~JoSon();
    static JoSon * fromString(std::string strJoson, std::string * sError);
    static JoSon * fromFile(std::string fileJoson, std::string * sError);

    std::string toString() const { return m_pRoot->toString(); };
    int toInt() const { return m_pRoot->toInt(); };
    double toDouble() const { return m_pRoot->toDouble(); };
    JoS_Element& operator[](int idx) const { return (*m_pRoot)[idx]; };
    JoS_Element& operator[](std::string key) const { return (*m_pRoot)[key]; };
    bool isMap() const { return m_pRoot->isMap(); };
    bool isList() const { return m_pRoot->isList(); };
    bool isLeaf() const { return m_pRoot->isLeaf(); };
    bool isNull() const { return m_pRoot->isNull(); };
    int size() const { return m_pRoot->size(); };

private:
    JoSon();
    JoS_Element * readAny(std::stringstream * stream);
    JoS_Map * readMap(std::stringstream * stream);
    JoS_List * readList(std::stringstream * stream);
    JoS_Leaf * readLeaf(std::stringstream * stream);
    std::string readString(std::stringstream * stream);
    char getNextChar(std::stringstream * stream);
    bool expect(std::stringstream * stream, char expected);

    JoS_Element * m_pRoot;
    std::string m_sError;
};

#endif
