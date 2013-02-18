#ifndef _JOSON_H
#define _JOSON_H

#include "JoS_Leaf.h"
#include "JoS_List.h"
#include "JoS_Map.h"

class JoSon
{
public:
    // Destructor
    ~JoSon();
    static JoSon * fromString(std::string strJoson, std::string * sError);
    static JoSon * fromFile(std::string fileJoson, std::string * sError);

    std::string toString() { return m_pRoot->toString(); };
    int toInt() { return m_pRoot->toInt(); };
    double toDouble() { return m_pRoot->toDouble(); };
    JoS_Element * get() { return m_pRoot->get(); };
    JoS_Element * get(int idx) { return m_pRoot->get(idx); };
    JoS_Element * get(std::string key) { return m_pRoot->get(key); };

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
