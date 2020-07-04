#pragma once
#ifndef _TREENODE_H_
#define _TREENODE_H_
#include <iostream>
#include <string.h>


class CTreeNode {
private:
    char* m_Destination;
    int m_Flight;
    char* m_Passengername;
    struct m_Flightdate {
        int date;
        int mounth;
        int year;
    };
    int condition;
    m_Flightdate* dateFl;
public:
    CTreeNode();
    char* SetValueObj(const char*, int);
    void* GetField(int);
    void PrintObj();
    ~CTreeNode();
};

#endif // !_TREENODE_H_