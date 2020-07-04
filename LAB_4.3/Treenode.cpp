#define _CRT_SECURE_NO_WARNINGS
#include "Treenode.h"

CTreeNode::CTreeNode() {
    m_Destination = NULL;
    m_Passengername = NULL;
    dateFl = NULL;
    m_Flight = 0;
    condition = 0;
}

CTreeNode::~CTreeNode() {
    delete[] m_Destination;
    delete[] m_Passengername;
    delete dateFl;
}

int readLenSegmant(const char* str, int& len, char elem) {
    int i;
    for (i = 0; i < len; i++) {
        if (str[i] == elem || str[i] == '\0')
            break;
    }
    return i;
}



char* CTreeNode::SetValueObj(const char* str, int len) {
    int lenSeg = readLenSegmant(str, len, ';');
    len -= lenSeg;
    m_Destination = new char[lenSeg + 1];
    strncpy(m_Destination, str, lenSeg);
    m_Destination[lenSeg] = '\0';
    str = str + lenSeg + 1;
    m_Flight = atoi(str);
    lenSeg = readLenSegmant(str, len,';');
    len -= lenSeg;
    str = str + lenSeg + 1;
    lenSeg = readLenSegmant(str, len, ';');
    m_Passengername = new char[lenSeg + 1];
    strncpy(m_Passengername, str, lenSeg);
    m_Passengername[lenSeg] = '\0';
    char* strRet = new char[lenSeg + 1];
    strcpy(strRet, m_Passengername);
    lenSeg = readLenSegmant(str, len, ';');
    len -= lenSeg;
    str = str + lenSeg + 1;
    lenSeg = readLenSegmant(str, len, ';');
    dateFl = new m_Flightdate;
    dateFl->date = atoi(str);
    lenSeg = readLenSegmant(str, len, '.');
    str = str + lenSeg + 1;
    dateFl->mounth = atoi(str);
    lenSeg = readLenSegmant(str, len, '.');
    str = str + lenSeg + 1;
    dateFl->year = atoi(str);
    lenSeg = readLenSegmant(str, len, '.');
    str = str + lenSeg + 1;
    return strRet;
}

void CTreeNode::PrintObj() {
    printf("\nDestination: %s\n", this->m_Destination);
    printf("Flight: %d\n", this->m_Flight);
    printf("Passengername: %s\n", this->m_Passengername);
    printf("date: %d\n", this->dateFl->date);
    printf("mounth: %d\n", this->dateFl->mounth);
    printf("year: %d\n\n", this->dateFl->year);
}

void* CTreeNode::GetField(int field) {
    switch (field)
    {
    case 1:
        switch (condition) {
        case 0:
            condition++;
            return &(this->m_Flight);
            break;
        case 1:
            condition++;
            return &(this->dateFl->date);
            break;
        case 2:
            condition++;
            return &(this->dateFl->mounth);
            break;
        case 3:
            condition = 0;
            return &(this->dateFl->year);
            break;
        default:
            condition = 0;
            return NULL;
            break;
        }
        break;
    case 3:
        return this->m_Passengername;
        break;
    case 4:
        return this->m_Destination;
        break;
    default:
        return NULL;
        break;
    }
}