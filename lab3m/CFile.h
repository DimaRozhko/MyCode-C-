#pragma once
#include "Iterator.h"
#include <ostream>
#include <cstring>
#define LEN 255
using namespace std;

class CFile{
public:
	friend bool operator==(CFile& obj1, CFile& obj2);
	friend ostream& operator<<(ostream& stream, CFile &obj);
	void setAll(string);
	int getDay();
	int getMonth();
	int getYear();
	char* getFilename(){return _filename;}
	void setFilename(const char* nFile){strcpy(_filename, nFile);}
private:
	char *_filename;
	char *_creation_date;
	int _size;
};