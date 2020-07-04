/*******************************************
*file: Bus.h
*last modified: 01.05.2020
*********************************************/
#pragma once
#include <ostream>
#include <cstring>
using namespace std;

class Bus
{
public:   
/*
methods
*/
	friend ostream& operator<<(ostream& stream, Bus &obj);
	friend bool operator==(Bus& obj1, Bus& obj2);
	void setAllFields(string);
	char* GetRouteNum();
	char* GetBusNum();
	char* GetDriver();
	void setDriver(const char*);

private:
	char *driver;
	char *bus_number;
	char *route_number;
};

