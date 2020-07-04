#include "CFile.h"

ostream& operator<<(ostream& stream, CFile &obj){
    stream << obj._filename << '\t' << obj._creation_date << '\t' << obj._size << endl;
}

int CFile::getDay(){
    string tmp;
    tmp = _creation_date;
    tmp.resize(tmp.find_first_of('/'));
    return atoi(tmp.c_str());
}

int CFile::getMonth(){
    string tmp;
    tmp = _creation_date;
    tmp.erase(0, tmp.find_first_of('/') + 1);
    tmp.resize(tmp.find_first_of('/'));
    return atoi(tmp.c_str());
}

int CFile::getYear(){
    string tmp;
    tmp = _creation_date;
    tmp.erase(0, tmp.find_first_of('/') + 1);
    tmp.erase(0, tmp.find_first_of('/') + 1);
    return atoi(tmp.c_str());
}

void CFile::setAll(string str){
    _filename = new char[225];
    _creation_date = new char[225];
    string strTmp;
    strTmp = str;
    strTmp.resize(strTmp.find_first_of(';'));
    strcpy(_filename, strTmp.c_str());
    str.erase(0, str.find_first_of(';') + 1);
    strTmp = str;
    strTmp.resize(strTmp.find_first_of(';'));
    strcpy(_creation_date, strTmp.c_str());
    str.erase(0, str.find_first_of(';') + 1);
    _size = atoi(str.c_str());
}

bool operator==(CFile& obj1, CFile& obj2){
    if((strcmp(obj1._creation_date, obj2._creation_date) == 0) &&
        (strcmp(obj1._filename, obj2._filename) == 0) &&
        (obj1._size == obj2._size))
        return true;
    else 
        return false;
}
